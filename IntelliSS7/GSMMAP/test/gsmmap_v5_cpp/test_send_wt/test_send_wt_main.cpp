////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: INTERNAL                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: test_send_wt_main.cpp,v 9.1 2005/03/23 12:51:37 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  GSM MAP V5 send (with toolkit) example.
//
//  This example shows how to send the argument of an GSM MAP Insert Subscriber 
//  Data operation. The part used to build (create, insert data and encode) the 
//  Insert Subscriber Data operation argument is identical the test_codec example.
//  This example uses the IntelliNet toolkit to demonstrate its routing
//  capabilities to a specific worker thread, based on the dialogue id.

//
//  IntelliNet SS7 stack note:
//
//  The conditional sections of the code that are included if the preprocessor
//  symbol "USE_INTELLINET_STACK" is defined are required only if the IntelliNet
//  SS7 stack is used. The IntelliNet SS7 stack allows to run the example
//  without any SS7 hardware.
//
//

//
//  C++ related note:
//  
//  The code relies on STL (C++ Standard Template Library). A basic knowledge
//  of STL is assumed (mainly classes std::vector and std::list). Likewise, a 
//  basic knowledge of C++ standard classes (e.g. std::string, std::ostream...) 
//  is also assumed. 
// 


#include <its++.h>

#if !defined(WIN32)
#include <signal.h>
#endif // defined(WIN32)

#include <iostream>

#include <its_app.h>
#include <its_transports.h>

#if defined(USE_INTELLINET_STACK)
#include <its_thread.h>
#include <its_thread_pool.h>
#include <its_worker.h>
#include <its_semaphore.h>
#include <its_object.h>
#include <its_object.h>
#include <its_timers.h>

extern "C" ITS_Class itsINTELLISS7_Class;
#endif // defined(USE_INTELLINET_STACK)

#include <itu/sccp.h>
#include <itu/tcap.h>
#include <tcap++.h>

#include <Asn.h>
#include <AsnException.h>

#include <map_cpp.h>
#include <map_v5_insert_subscriber_data_arg.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace map_common;
using namespace map_v5;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  Temporary work around for missing symbols in IntelliNet Vendor Library.
//
//  => Must be removed when problem will be corrected.
//

extern "C" {

int ISUP_SetVariant_CCITT() { return 0; }
int CCITT_CallTable;
int CCITT_ISUP_Variant() { return 0; }
int ISUP_TlvEventToL3Message_CCITT() { return 0; }
int ISUP_L3MessageToTlvEvent_CCITT() { return 0; }
int ComputeMSize() { return 0; }

}


////////////////////////////////////////////////////////////////////////////////
//
//  Local function declarations.
//

void Initialize(int argc, char** argv);
void Terminate();
void WorkerTcapThreadFunction(its::ITS_ThreadPoolThread* thr, void* arg);
static void WorkerTcapThreadFunctionTerminate(
                                ITS_HANDLE handle,
                                ITS_Worker* worker,
                                TCAP_Dialogue* dlg,
                                TCAP_Component* cpt,
                                bool& routeDeleted,
                                bool& initialized);
ITS_USHORT ApplicationSelector(ITS_HDR* hdr, ITS_EVENT* event);
vector<byte> BuildOperationInsertSubscriberDataArg();


////////////////////////////////////////////////////////////////////////////////
//
//  Macros.
//

#define WORKER_NUMBER(workerInstance) \
            (workerInstance - WORKER_POOL_START_INSTANCE)


////////////////////////////////////////////////////////////////////////////////
//
//  Forward declaration.
//

class WorkerPool;
class DispatcherPool;


////////////////////////////////////////////////////////////////////////////////
//
//  Global variables.
//

static WorkerPool* workerPool;
static DispatcherPool* dispatcherPool;
static int workerPoolSize = 16;
static int dispatcherPoolSize = 1;
static bool stopRequested = false;
static int sendCount = 2;


////////////////////////////////////////////////////////////////////////////////
//
//  Definitions for SCCP addresses.
//

#define SCCP_ADDR_INDICATOR (SCCP_CPA_ROUTE_NAT |   \
                             SCCP_CPA_ROUTE_SSN |   \
                             SCCP_CPA_HAS_PC    |   \
                             SCCP_CPA_HAS_SSN)


#define LOCAL_PC    0
#define LOCAL_SSN   3

#define REMOTE_PC   0
#define REMOTE_SSN  4


////////////////////////////////////////////////////////////////////////////////
//
//  Simple break handler (specific for WIN32 and Unix).
//

#if defined(WIN32)
static BOOL WINAPI breakHandler(DWORD ctrlType)
{
    Terminate();
    
    exit(EXIT_SUCCESS);
}
#else // !defined(WIN32)
static void exitHandler(int sig)
{
    Terminate();

    exit(EXIT_SUCCESS);
}
#endif // defined(WIN32)


#if defined(USE_INTELLINET_STACK)

////////////////////////////////////////////////////////////////////////////////
//
//  Synchronization object (semaphore) used to synchronize primary thread and
//  border transport thread.
//

static ITS_Semaphore borderTransportSemaphore(0);

#endif // defined(USE_INTELLINET_STACK)


//
// Mapping of fixed thread instances
//

enum {

    // Dispatcher pool.

    DISPATCHER_POOL_START_INSTANCE  = 2,

    DISPATCHER_POOL_MINIMUM_SIZE    = 1,
    DISPATCHER_POOL_MAXIMUM_SIZE    = 128,

    // Worker pool.

    WORKER_POOL_START_INSTANCE      = DISPATCHER_POOL_START_INSTANCE +
                                        DISPATCHER_POOL_MAXIMUM_SIZE,

    WORKER_POOL_MINIMUM_SIZE        = 16,
    WORKER_POOL_MAXIMUM_SIZE        = 1024
};


//.interface:DispatcherPool
//////////////////////////////////////////////////////////////////////////////
//  Interface:
//      DispatcherPool.
//
//  Purpose:
//      The DispatcherPool class defines the interface for a thread
//      pool that is used for the dispatchers in the application. A
//      dispatcher thread is one that is in a forever loop, waiting
//      for another request on its transport.
//
//  Usage:
//      This class inherits from the ITS Thread Pool class to get the
//      common properties and methods. Specific functions to dispatch 
//      each of the application interface points are added here.
//
//////////////////////////////////////////////////////////////////////////////
class DispatcherPool : public ITS_ThreadPool
{
public:
    //.implementation:public,inline,DispatcherPool
    ///////////////////////////////////////////////////////////////////////////
    //  Purpose:
    //      This is the constructor for a DispatcherPool object.
    //
    //  Input Parameters:
    //      sizeParam - size (number of threads) in the pool.
    //
    //  Input/Output Parameters:
    //      None.
    //
    //  Output Parameters:
    //      None.
    //
    //  Return Value:
    //      None.
    //
    //  Notes:
    //
    //  See Also:
    //      ~DispatcherPool()
    ///////////////////////////////////////////////////////////////////////////
    DispatcherPool(unsigned short sizeParam)
    :   ITS_ThreadPool(),
        startInstance(DISPATCHER_POOL_START_INSTANCE),
        size(sizeParam),
        count(0)
    {
        ITS_REQUIRE(sizeParam >= MINIMUM_SIZE);
        ITS_REQUIRE(sizeParam <= MAXIMUM_SIZE);
    }

    //.implementation:public,inline,DispatcherPool
    ///////////////////////////////////////////////////////////////////////////
    //  Purpose:
    //      This is the destructor for a DispatcherPool object.
    //
    //  Input Parameters:
    //      None.
    //
    //  Input/Output Parameters:
    //      None.
    //
    //  Output Parameters:
    //      None.
    //
    //  Return Value:
    //      None.
    //
    //  Notes:
    //
    //  See Also:
    //      DispatcherPool()
    ///////////////////////////////////////////////////////////////////////////
    virtual ~DispatcherPool()
    {
    }

    virtual ITS_ThreadPoolThread* CreatePoolThread(int stackSize);

    //.implementation:public,inline,DispatcherPool
    ////////////////////////////////////////////////////////////////////////////
    //  Purpose:
    //      This method is used to get the number of threads in the
    //      thread pool.
    //
    //  Input Parameters:
    //      None.
    //
    //  Input/Output Parameters:
    //      None.
    //
    //  Output Parameters:
    //      None.
    //
    //  Return Value:
    //      size (number of threads) in the pool.
    //
    //  Notes:
    //
    //  See Also:
    //      
    ////////////////////////////////////////////////////////////////////////////
    unsigned short
    GetSize()
    { return size; }

    enum
    {
        SS7_DISPATCHER_THREAD_INDEX     = 0
    };

    enum
    {
        MINIMUM_SIZE = DISPATCHER_POOL_MINIMUM_SIZE,
        MAXIMUM_SIZE = DISPATCHER_POOL_MAXIMUM_SIZE
    };

    // Specific thread functions (one specific thread function for each specific
    // dispatcher thread).

    static void SS7_ThreadFunction(ITS_ThreadPoolThread* thr, void* arg);
    
protected:

    unsigned short startInstance;
    unsigned short size;

    unsigned short count;

private:
    //.implementation:private,inline,DispatcherPool
    /////////////////////////////////////////////////////////////////////////////
    //  Purpose:
    //      This is the copy constructor for the DispatcherPool object.
    //
    //  Input Parameters:
    //      None.
    //
    //  Input/Output Parameters:
    //      None.
    //
    //  Output Parameters:
    //      None.
    //
    //  Return Value:
    //      None.
    //
    //  Notes:
    //      This is not implemented since only once instance is allowed
    //      in a program.
    //
    //  See Also:
    //      ~DispatcherPool()
    /////////////////////////////////////////////////////////////////////////////
    DispatcherPool(const DispatcherPool&) {};

    //.implementation:private,inline,DispatcherPool
    /////////////////////////////////////////////////////////////////////////////
    //  Purpose:
    //      This method is the assignment operator for the DispatcherPool 
    //      object.
    //
    //  Input Parameters:
    //      None.
    //
    //  Input/Output Parameters:
    //      None.
    //
    //  Output Parameters:
    //      None.
    //
    //  Return Value:
    //      None.
    //
    //  Notes:
    //
    //  See Also:
    //      
    /////////////////////////////////////////////////////////////////////////////
    DispatcherPool& operator=(const DispatcherPool&)
    { return *this; }

};


//.implementation:public
///////////////////////////////////////////////////////////////////////////////
//
//  Purpose:
//      This method is used to create the next thread in the thread 
//      pool. Since each of the dispatchers is given a fixed thread
//      instance, this class maintains the instance for the last
//      dispatcher thread created, this information is used to
//      determine what kind of thread (transport) is to created next. 
//
//  Input Parameters:
//      stackSize - stack size (bytes) for the thread.
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      pointer to the thread that was created.      
//
//  Notes:
//      The method is called multipe times. Each time it is called,
//      the "next" dispatcher thread is created with the transport
//      parameters appropriate for that kind of thread.
//
//  See Also:
//
///////////////////////////////////////////////////////////////////////////////
ITS_ThreadPoolThread* DispatcherPool::CreatePoolThread(int stackSize)
{
    ITS_Worker* result = NULL;

    unsigned short currentInstance = count + startInstance;

    if (currentInstance == startInstance + SS7_DISPATCHER_THREAD_INDEX)
    {
        // Create SS7 dispatcher.

#if defined(USE_INTELLINET_STACK)


#if defined(USE_SOCKETS)

        result = new ITS_Worker(stackSize, "IntelliNet Stack SS7 Dispatcher",
                                currentInstance,
                                ITS_SCCP                    |
                                ITS_TRANSPORT_CSOCKET       |
                                ITS_TRANSPORT_DELAY_CREATE);

#else // !defined(USE_SOCKETS)

        result = new ITS_Worker(stackSize, "IntelliNet Stack SS7 Dispatcher",
                                currentInstance,
                                ITS_SCCP            |
                                ITS_TRANSPORT_FIFO  |
                                ITS_TRANSPORT_DELAY_CREATE);

#endif // defined(USE_SOCKETS)


#else // !defined(USE_INTELLINET_STACK)

        result = new ITS_Worker(stackSize, "SS7 Dispatcher",
                                currentInstance,
                                ITS_TCAP | ITS_SCCP | ITS_TRANSPORT_SS7 |
                                ITS_TRANSPORT_DELAY_CREATE);

#endif // defined(USE_INTELLINET_STACK)

    }
 
    count++;

    ITS_ENSURE(result != NULL);

    return (ITS_ThreadPoolThread *)result;
}



//.implementation:public
///////////////////////////////////////////////////////////////////////////////
//
//  Purpose:
//      This method is the SS7 Dispatcher thread function. In other 
//      words, the dispatcher thread that handles requests from the 
//      SS7 stack is dispatched with this function. 
//
//  Input Parameters:
//      thr - pointer to the thread object.
//      arg - specific arguments passed in to the thread function.
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      None.      
//
//  Notes:
//
//  See Also:
//
///////////////////////////////////////////////////////////////////////////////
void 
DispatcherPool::SS7_ThreadFunction(ITS_ThreadPoolThread* thr, void* arg)
{

    ITS_REQUIRE(thr != NULL);

    ITS_Worker* worker      = static_cast<ITS_Worker*> (thr);
    ITS_HANDLE handle       = NULL;

    ITS_Event event;

    handle = ITS_Initialize(worker->GetMask(), worker->GetInstance());

    if (handle == NULL)
    {
        ITS_Error itsError(ITS_ENOTRANSPORT, __FILE__, __LINE__);

        cout << endl << itsError.GetDescription() << endl;

        return;
    }

    // To signal primary thread that the border transport thread is running and
    // that the associated transport is initialized.

    borderTransportSemaphore.Post();

    while (!worker->GetExit())
    {
        int res = worker->GetNextEvent(event);

        if (res != ITS_SUCCESS)
        {
            ITS_Error itsError(res, __FILE__, __LINE__);

            cout << endl << itsError.GetDescription() << endl;
        }
        else
        {
            // Set event source to MTP3 (for routing purpose).

            event.SetSource(ITS_MTP3_SRC);

            // Send event to IntelliNet stack (SCCP layer).
        
            ITS_Transport::PutEvent(ITS_SCCP_SRC, event);
        }
    }

    ITS_Terminate(handle);

    return;
}


//.interface:WorkerPool
//////////////////////////////////////////////////////////////////////////////
//  Interface:
//      WorkerPool.
//
//  Purpose:
//      The WorkerPool class defines the interface for a thread
//      pool that is used for the executors (workers) in the example. 
//      A worker thread is dispatched to process a message received
//      by the receiver.
//
//  Usage:
//      This class inherits from the ITS Thread Pool class to get the
//      common properties and methods. 
//
//////////////////////////////////////////////////////////////////////////////
class WorkerPool : public ITS_ThreadPool
{
public:
    //.implementation:public,inline,WorkerPool
    ///////////////////////////////////////////////////////////////////////////
    //  Purpose:
    //      This is the constructor for a WorkerPool object.
    //
    //  Input Parameters:
    //      sizeParam - size (number of threads) in the pool.
    //
    //  Input/Output Parameters:
    //      None.
    //
    //  Output Parameters:
    //      None.
    //
    //  Return Value:
    //      None.
    //
    //  Notes:
    //
    //  See Also:
    //      ~WorkerPool()
    ///////////////////////////////////////////////////////////////////////////
    WorkerPool(unsigned short sizeParam)
    :   ITS_ThreadPool(),
        startInstance(WORKER_POOL_START_INSTANCE),
        size(sizeParam),
        count(0)
    {
        ITS_REQUIRE(sizeParam >= MINIMUM_SIZE);
        ITS_REQUIRE(sizeParam <= MAXIMUM_SIZE);
    }
    //.implementation:public,inline,WorkerPool
    ////////////////////////////////////////////////////////////////////////////
    //  Purpose:
    //      This is the destructor for a WorkerPool object.
    //
    //  Input Parameters:
    //      None.
    //
    //  Input/Output Parameters:
    //      None.
    //
    //  Output Parameters:
    //      None.
    //
    //  Return Value:
    //      None.
    //
    //  Notes:
    //
    //  See Also:
    //      WorkerPool()
    ////////////////////////////////////////////////////////////////////////////
    virtual ~WorkerPool()
    {
        // Nothing to do.
    }

    virtual ITS_ThreadPoolThread* CreatePoolThread(int stackSize);

    //.implementation:public,inline,WorkerPool
    ////////////////////////////////////////////////////////////////////////////
    //  Purpose:
    //      This method is used to get the number of threads in the
    //      thread pool.
    //
    //  Input Parameters:
    //      None.
    //
    //  Input/Output Parameters:
    //      None.
    //
    //  Output Parameters:
    //      None.
    //
    //  Return Value:
    //      size (number of threads) in the pool.
    //
    //  Notes:
    //
    //  See Also:
    //      
    ////////////////////////////////////////////////////////////////////////////
    unsigned short
    GetSize()
    {
        return size;
    }

    enum
    {
        MINIMUM_SIZE = WORKER_POOL_MINIMUM_SIZE,
        MAXIMUM_SIZE = WORKER_POOL_MAXIMUM_SIZE
    };

    
protected:

    unsigned short startInstance;
    unsigned short size;

    unsigned short count;

private:
    //.implementation:private,inline,WorkerPool
    /////////////////////////////////////////////////////////////////////////////
    //  Purpose:
    //      This is the copy constructor for the WorkerPool object.
    //
    //  Input Parameters:
    //      None.
    //
    //  Input/Output Parameters:
    //      None.
    //
    //  Output Parameters:
    //      None.
    //
    //  Return Value:
    //      None.
    //
    //  Notes:
    //      This is not implemented since only once instance is allowed
    //      in a program.
    //
    //  See Also:
    //      ~WorkerPool()
    /////////////////////////////////////////////////////////////////////////////
    WorkerPool(const WorkerPool&) {};

    //.implementation:private,inline,WorkerPool
    /////////////////////////////////////////////////////////////////////////////
    //  Purpose:
    //      This method is the assignment operator for the WorkerPool 
    //      object.
    //
    //  Input Parameters:
    //      None.
    //
    //  Input/Output Parameters:
    //      None.
    //
    //  Output Parameters:
    //      None.
    //
    //  Return Value:
    //      None.
    //
    //  Notes:
    //
    //  See Also:
    //      
    /////////////////////////////////////////////////////////////////////////////
    WorkerPool& operator=(const WorkerPool&)
    { return *this; }

};


//.implementation:public
///////////////////////////////////////////////////////////////////////////////
//
//  Purpose:
//      This method is used to create the next thread in the thread 
//      pool. The thread created is given the next instance number
//      that is availiable. 
//
//  Input Parameters:
//      stackSize - stack size (bytes) for the thread.
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      pointer to the thread that was created.      
//
//  Notes:
//      The method is called multipe times. Each time it is called,
//      the "next" executor (worker) thread is created with the transport
//      parameters appropriate for an executor thread (Queue).
//
//  See Also:
//
///////////////////////////////////////////////////////////////////////////////
ITS_ThreadPoolThread* WorkerPool::CreatePoolThread(int stackSize)
{
    ITS_Worker* result = NULL;

    unsigned short currentInstance = count + startInstance;

    char workerName[64];

    sprintf(workerName,"Worker Thread %d", count);

    result = new ITS_Worker(stackSize,
                            workerName,
                            currentInstance,
                            ITS_TRANSPORT_TQUEUE | ITS_TRANSPORT_DELAY_CREATE);

    count++;

    ITS_ENSURE(result != NULL);

    return (ITS_ThreadPoolThread *)result;
}



//.implementation:extern
///////////////////////////////////////////////////////////////////////////
//  Purpose:
//      This is the Application Selector function for the application.
//      This function is registered with IntelliSS7 on application startup.
//      It is called by the IntelliSS7 Routing Subsystem in case a SS7 
//      message is received from the SS7 stack and the dialogue id 
//      associated with the message is not present in the Routing table.
//
//  Input Parameters:
//      hdr - dialogue information.
//      event - the event received from the stack.
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      ITS_NO_SRC.
//
//  Notes:
//
//  See Also:
//      
///////////////////////////////////////////////////////////////////////////
extern "C" ITS_USHORT
AppSelect(ITS_HDR *hdr, ITS_EVENT *event)
{
    return ApplicationSelector(hdr, event);
}



//.implementation:public
///////////////////////////////////////////////////////////////////////////
//  Purpose:
//      This method performs all the initialization functions for
//      the application. Here are the specific steps performed:
// 
//  Application initialization.
//
//  o Initialization of IntelliSS7 subsystems.
//
//  o Set Application Selector.
//
//  o Create worker thread pool.
//
//  Input Parameters:
//      argc - argument count.
//      argv - argument variables.
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      None.
//
//  Notes:
//
//  See Also:
//      
///////////////////////////////////////////////////////////////////////////
void 
Initialize(int argc, char** argv)
{
    bool globalStartSuccess = false;

    try
    {
        ////////////////////////////////////////////////////////////////////////
        //
        //  Set application name.
        //

        ITS_Application::SetName("test_send_wt");


#if defined(USE_INTELLINET_STACK)

        ////////////////////////////////////////////////////////////////////////
        //
        //  Using IntelliSS7 stack (add that feature).
        //

        int res = ITS_AddFeature(itsINTELLISS7_Class);

        if (res != ITS_SUCCESS)
        {
            throw ITS_Error(res, __FILE__, __LINE__); // Fatal error.
        }

#endif // defined(USE_INTELLINET_STACK)


        ////////////////////////////////////////////////////////////////////////
        //        
        //  IntelliSS7 subsystems initialization (including licensing).
        //

        res = ITS_GlobalStart(ITS_TCAP | ITS_SCCP);

        if (res != ITS_SUCCESS)
        {
            throw ITS_Error(res, __FILE__, __LINE__); // Fatal error.
        }

 

        //
        // Set Application Selector for MRVT Server.
        //

        ROUTE_Selector previousSelector = 
            ROUTE_SetApplicationSelector(AppSelect);

        ITS_ASSERT(previousSelector != NULL);


        // Thread pools not related to dispatching must be created first.

        //
        // Create worker thread pool.
        //

        try
        {
            workerPool = new WorkerPool(workerPoolSize);

            workerPool->CreatePool(workerPool->GetSize(), 0);
        }
        catch (ITS_GenericException& exc)
        {
            cout << "Failed to create worker thread pool." << endl;
            exc.Log();

            workerPool = NULL;

            throw exc;
        }
        catch (exception& exc)
        {
            cout << "Failed to create dispatcher thread pool." << endl;
            ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);

            standardExc.Log();

            workerPool = NULL;

            throw exc;
        }


#if defined(USE_INTELLINET_STACK)

        //
        // Create dispatcher thread pool.
        //

        try
        {
            dispatcherPool = new DispatcherPool(dispatcherPoolSize);

            dispatcherPool->CreatePool(dispatcherPool->GetSize(), 0);
        }
        catch (ITS_GenericException& exc)
        {
            cout << "Failed to create dispatcher thread pool." << endl;
            exc.Log();

            dispatcherPool = NULL;

            throw exc;
        }
        catch (exception& exc)
        {
            cout << "Failed to create dispatcher thread pool." << endl;

            ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);

            standardExc.Log();

            dispatcherPool = NULL;

            throw exc;
        }

        //
        // Set dispatcher thread functions and start dispatcher threads. The
        // order that threads are allocated is the same as the order they were
        // created in the thread pool. Relevant and very important in this case.
        // The order MUST be exactly the same than in the member function
        // DispatcherPool::CreatePoolThread.
        //

        res = dispatcherPool->Dispatch
                                (DispatcherPool::SS7_ThreadFunction, 
                                 NULL);

        if (res != ITS_SUCCESS)
        {
            ITS_THROW_ERROR(res);
        }  

        borderTransportSemaphore.Wait(); 

#endif // defined(USE_INTELLINET_STACK)

        // No exception handled.

        cout << "Application startup initialization complete" << endl;
 
        return;
    }
    catch (ITS_GenericException& exc)
    {
        cout << exc.GetDescription().c_str() << endl;

        exc.Log();
    }
    catch (exception& exc)
    {
        cout << "C++ exception " << exc.what() << endl;

        ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);
        standardExc.Log();
    }

    // Reached only if an exception has occurred.

    stopRequested = true;

    return;
}


//
//.implementation:public
///////////////////////////////////////////////////////////////////////////
//  Purpose:
//      This method performs all the termination functions for
//      the application. Here are the specific steps performed:
// 
//  Application termination.
//
//  o Delete worker pool.
// 
//  o Termination of IntelliSS7 subsystems.
// 
//  o ...
//
//  Input Parameters:
//      None.
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      None.
//
//  Notes:
//
//  See Also:
//      
///////////////////////////////////////////////////////////////////////////
void
Terminate()
{
    cout << "Application being terminated" << endl;

    try 
    {
        //
        // Try to delete worker pool.
        //

        if (workerPool)
        {
            delete workerPool;

            workerPool = NULL;

            //
            // Wait for activity to cease.
            //

            ITS_ThreadPool::WaitForDeletionComplete();
        }

#if defined(USE_INTELLINET_STACK)

            delete dispatcherPool;

            dispatcherPool = NULL;

            //
            // Wait for activity to cease.
            //

            ITS_ThreadPool::WaitForDeletionComplete();

#endif // defined(USE_INTELLINET_STACK)
   
        ////////////////////////////////////////////////////////////////////////
        //
        //  IntelliSS7 termination.
        //

        ITS_GlobalStop();


#if defined(USE_INTELLINET_STACK)

        ////////////////////////////////////////////////////////////////////////
        //
        //  Using IntelliSS7 stack (remove feature).
        //

#endif // defined(USE_INTELLINET_STACK)

    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;

        ITS_GlobalStop();

        exit(EXIT_FAILURE);
    }

}


//.implementation:
/////////////////////////////////////////////////////////////////////////////
//  Purpose:
//      This function is executed by the the TCAP handler thread.
//
//  Input Parameters:
//      thr -   pointer to the executor thread.
//      arg -   argument passed to the thread function.
//              NULL is passed to the thread function.   
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      None.
//
//  Notes:
//
//  See Also:
/////////////////////////////////////////////////////////////////////////////
void 
WorkerTcapThreadFunction(its::ITS_ThreadPoolThread* thr, void* arg)
{
    ITS_REQUIRE(thr != NULL);

    ITS_HANDLE handle   = NULL;
    ITS_Worker* worker  = static_cast<ITS_Worker*>(thr);

    TCAP_Dialogue* dlg  = NULL;
    TCAP_Component* cpt = NULL;

    cout << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")" <<
            " **** -> Entering WorkerTcapThreadFunction." << endl;

    //
    //  Note: route has been previously added by Application Selector.
    //

    bool routeDeleted   = false;
    bool initialized    = false;

    try
    {
        // Initialize and get transport handle.

        handle = ITS_Initialize(worker->GetMask(), worker->GetInstance());

        if (handle == NULL)
        {
            ITS_THROW_ERROR(ITS_ENOTRANSPORT);
        }
  
        initialized = true;

        ////////////////////////////////////////////////////////////////////////
        //
        //  Execute GSM MAP operation Insert Subscriber Data:
        //  
        //  o   Allocate new dialogue ID.
        //
        //  o   Build TCAP begin dialogue.
        //
        //  o   Build TCAP invoke component.
        //
        //  o   Call function to build GSM MAP Insert Subscriber Data operation 
        //      argument.
        //
        //  o   Send TCAP invoke component.
        //  
        //  o   Send TCAP begin dialogue.
        //


        ITS_USHORT dialogueID = 0;

        TCAP_AllocateDialogueId(&dialogueID);


        // Create begin dialogue (dlg) object and populate it.

        TCAP_Begin beginDlg;

        beginDlg.SetDialogueID(dialogueID);

        beginDlg.SetOrigAddr(
                    SCCP_ADDR_INDICATOR, 
                    LOCAL_PC, 
                    LOCAL_SSN, 
                    NULL, 
                    0);

        beginDlg.SetDestAddr(
                    SCCP_ADDR_INDICATOR, 
                    REMOTE_PC, 
                    REMOTE_SSN, 
                    NULL, 
                    0);

        // Create invoke component (cpt) object and populate it.

        TCAP_Invoke invokeCpt;

        invokeCpt.SetInvokeID(1);

        // "OP_insertSubscriberData" is defined in file inap_cpp.h.

        invokeCpt.SetOperation(OP_insertSubscriberData); 

        // Class 2 (only errors appear in the GSM MAP Insert Subscriber Data 
        // operation macro, see GSM MAP recommendation Q.XXXX).

        invokeCpt.SetClass(2);

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Function call uses GSM MAP ASN.1 C++ API.
    //

        vector<byte> encodedInsertSubscriberDataArg = 
                BuildOperationInsertSubscriberDataArg();

    //
    ////////////////////////////////////////////////////////////////////////////


        // The parameter field of the TCAP invoke component contains the GSM MAP
        // Insert Subscriber Data operation argument.

        invokeCpt.SetParameter(encodedInsertSubscriberDataArg);


        cout << endl << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")"
             << "Ready to execute GSM MAP Insert Subscriber Data operation..." 
             << endl;
      
        TCAP_Component::Send(handle, &beginDlg, &invokeCpt);

        TCAP_Dialogue::Send(handle, &beginDlg);

        //
        //  Worker instance is associated transport instance.
        //

        ITS_USHORT transportInstance = worker->GetInstance();
        
        ITS_HDR hdr;

        hdr.type = ITS_TCAP;
    
        hdr.context.dialogue_id = dialogueID;
        
        int res = ROUTE_AddApplication(transportInstance, &hdr);

        if (res != ITS_SUCCESS)
        {
            cout << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")" << 
                "Failed to execute ROUTE_AddApplication with error "
                << res << endl;

            ITS_THROW_ERROR(worker != NULL);
        }


        ////////////////////////////////////////////////////////////////////////
        //
        //  Receive loop:
        //  
        //  o   Receive TCAP end dialogue (sent by test_receive example).
        //
        //  o   Exit loop.
        //

        TCAP_Dialogue* recvDlg       = NULL;
        TCAP_Component* recvCpt      = NULL;
        ITS_USHORT currentDialogueID = 0;

        bool stop = false;

	    while (!stop)
	    {
            ITS_Event event;

		    int res = ITS_GetNextEvent(handle, &event.GetEvent());

            if (res != ITS_SUCCESS)
            {
                ITS_Error itsError(res, __FILE__, __LINE__);

                cout << endl << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")"
                     << itsError.GetDescription() << endl;

                continue;
            }

            cout << endl << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")"
                 << "Received Event..." << endl;

            cout << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")"
                 << "Source: <" << event.GetSource() << ">." << endl;

            if (TCAP_MSG_TYPE(&event.GetEvent()) == ITS_TCAP_CPT)
            {
                if (recvCpt != NULL)
                {
                    delete recvCpt;
                    recvCpt = NULL;
                }

                res = TCAP_Component::Receive(handle, event, recvDlg, &recvCpt);

                if (res != ITS_SUCCESS)
                {
                    throw ITS_Error(res, __FILE__, __LINE__); // Fatal error.
                }

                cout << endl << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")"
                     << "Receive TCAP component..." << endl;
            }
            else if (TCAP_MSG_TYPE(&event.GetEvent()) == ITS_TCAP_DLG)
            {
                if (recvDlg != NULL)
                {
                    delete recvDlg;
                    recvDlg = NULL;
                }

                res = TCAP_Dialogue::Receive(handle, event, &recvDlg);

                if (res != ITS_SUCCESS)
                {
                    throw ITS_Error(res, __FILE__, __LINE__); // Fatal error.
                }

                cout << endl << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")"
                     << "Received TCAP dialogue..." << endl;

                currentDialogueID = recvDlg->GetDialogueID();

                cout << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")"
                     <<"Dialogue ID: <" << currentDialogueID << ">." << endl;

                switch (recvDlg->GetDialogueType())
                {
                case TCAP_PT_TC_CONTINUE_CCITT:
                {
                    cout << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")"
                         << "Continue dialogue." << endl;

                    TCAP_Continue* recvContinueDlg = static_cast<TCAP_Continue*>(recvDlg);
                    
                    // Send an End dialogue to end the transaction.

                    TCAP_End endDlg;
                    
                    endDlg.SetDialogueID(currentDialogueID);
                    
                    TCAP_Dialogue::Send(handle, &endDlg);
                    
                    stop = true; // Exit receive loop.

                    break;
                }

                case TCAP_PT_TC_UNI_CCITT:
                case TCAP_PT_TC_BEGIN_CCITT:
                case TCAP_PT_TC_END_CCITT:
                case TCAP_PT_TC_P_ABORT_CCITT:
                case TCAP_PT_TC_U_ABORT_CCITT:
                case TCAP_PT_TC_NOTICE_CCITT:
                {
                    // Should be processed by complete code.

                    stop = true; // Exit receive loop.

                    break;
                }

                default:
                {
                    // Should not be reached.

                    break;
                }
                } // Switch.
            }
	    }



    
        ////////////////////////////////////////////////////////////////////////
        //
        //  IntelliSS7 termination.
        //

        ITS_Terminate(handle);


#if defined(USE_INTELLINET_STACK)

        ////////////////////////////////////////////////////////////////////////
        //
        //  Using IntelliSS7 stack (remove feature).
        //

        ITS_RemFeature(itsINTELLISS7_Class);

#endif // defined(USE_INTELLINET_STACK)



        WorkerTcapThreadFunctionTerminate(
                                        handle,
                                        worker,
                                        recvDlg,
                                        recvCpt,
                                        routeDeleted,
                                        initialized);




        cout << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")" <<
                " **** -> Exiting WorkerTcapThreadFunction." << endl;
        
        return; // No exception has occurred.
    }    
    catch (ITS_GenericException& exc)
    {
        exc.Log();

        cout << 
            "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")" <<
            "Caught ITS_GenericException " << exc.GetDescription().c_str() << endl;
    }
    catch (exception& exc)
    {
        ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);

        standardExc.Log();

        cout << 
            "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")" <<
            "Caught ITS_StandardException " << standardExc.GetDescription().c_str() << endl;
    }

#if defined(NDEBUG)

    catch (...)
    {
        ITS_UnknownException unknownExc(__FILE__, __LINE__);

        unknownExc.Log();

        cout << 
            "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")" <<
            "Caught ITS_UnknownException " << unknownExc.GetDescription().c_str() << endl;
    }

#endif  // defined(NDEBUG)

    WorkerTcapThreadFunctionTerminate(
                                    handle,
                                    worker,
                                    dlg,
                                    cpt,
                                    routeDeleted,
                                    initialized);

    cout << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")" <<
        " **** -> Exiting WorkerTcapThreadFunction." << endl;

    return; // Exception has occurred.
}



//.implementation:
/////////////////////////////////////////////////////////////////////////////
//  Purpose:
//      This function is a helper function for termination of the TCAP
//      message handling.
//
//  Input Parameters:
//      handle -   transport handle of the thread
//      worker - the worker thread
//      dlg - dialogue received
//      cpt - component received
//      routeDeleted - whether route has been deleted
//      initialized - whether dispatcher was initialized.  
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      None.
//
//  Notes:
//
//  See Also:
/////////////////////////////////////////////////////////////////////////////
static void
WorkerTcapThreadFunctionTerminate(
                                ITS_HANDLE handle,
                                ITS_Worker* worker,
                                TCAP_Dialogue* dlg,
                                TCAP_Component* cpt,
                                bool& routeDeleted,
                                bool& initialized)
{
    cout << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")" <<
        " **** -> Entering WorkerTcapThreadFunctionTerminate." << endl;

    if (!routeDeleted)
    {
        // Delete application route.

        ITS_HDR hdr;

        hdr.type = ITS_TCAP;
        hdr.context.dialogue_id = dlg->GetDialogueID();

        int res = ROUTE_DeleteApplication(worker->GetInstance(), &hdr);

        if (res != ITS_SUCCESS)
        {
            cout << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")" <<
                " **** <- Exiting WorkerTcapThreadFunctionTerminate." << endl;

            ITS_THROW_ERROR(res);
        }

        routeDeleted = true;
    }

    if (initialized)
    {
        ITS_Terminate(handle);
    }

    initialized = false;

    if (dlg != NULL)
    {
        delete dlg;
    }

    if (cpt != NULL)
    {
        delete cpt;
    }

    cout << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")" <<
        " **** <- Exiting WorkerTcapThreadFunctionTerminate." << endl;
}



//.implementation:public
///////////////////////////////////////////////////////////////////////////
//  Purpose:
//      This method performs the Application Selector function for the 
//      example. This is the only function called from the actual
//      App Selector function which is registered with IntelliSS7 on 
//      MRVT server startup.
//      It is called by the IntelliSS7 Routing Subsystem in case a SS7 
//      message is received from the SS7 stack and the dialogue id 
//      associated with the message is not present in the Routing table.
//
//  ApplicationSelector callback used by the IntelliSS7 routing mechanism 
//  (called only by the function ROUTE_SelectApplication).
//
//  Selection done according to the type of the event/message (ITS_TCAP).
//
//  TCAP => new dialogue. 
//
//      o Associate a thread from worker pool.
//
//  SCCP => new connexion. 
//
//      o Should not occur. Return ITS_NO_SRC.
//
//  If an error occurs, ITS_NO_SRC is returned.
//
//
//  Input Parameters:
//      hdr - dialogue information.
//      event - the event received from the stack.
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      ITS_NO_SRC.
//
//  Notes:
//
//  See Also:
//      
///////////////////////////////////////////////////////////////////////////
ITS_USHORT
ApplicationSelector(ITS_HDR* hdr, ITS_EVENT* event)
{
    int res = ITS_SUCCESS;

    try
    {
        switch (hdr->type)
        {
            case ITS_TCAP:
            {
                //
                // If this point is reached then the transaction dialogue id is
                // not in the application routing table. Therefore we need to:
                //
                // o Get a worker thread from the worker pool.
                //
                // o Update the application routing table.
                //
                // o Add thread function to the worker thread and resume it.
                //

                ITS_USHORT dialogue_id = hdr->context.dialogue_id;
            
                ITS_ThreadPoolEntry threadPoolEntry;

                res = workerPool->
                        GetFirstAvailThread(threadPoolEntry);
            
                if (res != ITS_SUCCESS)
                {
                    ITS_THROW_ERROR(res);
                }

                ITS_Worker* worker = 
                    static_cast<ITS_Worker*> (threadPoolEntry.GetThread());

                if (worker == NULL)
                {
                    workerPool->ReturnToAvailThreads(threadPoolEntry);

                    bool must_not_be_reached = false;

                    ITS_ASSERT(must_not_be_reached);

                    return ITS_NO_SRC;
                }

                //
                //  Worker instance is associated transport instance.
                //

                ITS_USHORT transportInstance = worker->GetInstance();

                res = ROUTE_AddApplication(transportInstance, hdr);

                if (res != ITS_SUCCESS)
                {
                    cout << 
                        "Failed to execute ROUTE_AddApplication with error "
                        << res << endl;

                    workerPool->
                        ReturnToAvailThreads(threadPoolEntry);

                    ITS_THROW_ERROR(worker != NULL);
                }


                res = workerPool->
                            DispatchOnThread(threadPoolEntry, 
                                             WorkerTcapThreadFunction,
                                             NULL);

                if (res != ITS_SUCCESS)
                {
                    workerPool->
                        ReturnToAvailThreads(threadPoolEntry);

                    ITS_THROW_ERROR(worker != NULL);
                }

                TIMERS_Sleep(1);

                return transportInstance;
            }

            default:
            {
                bool must_not_be_reached = false;

                ITS_ASSERT(must_not_be_reached);

                return ITS_NO_SRC;
            }
        }

        // Not reached.
    }
    catch (ITS_GenericException& exc)
    {
        exc.Log();
    }
    catch (exception& exc)
    {
        ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);

        standardExc.Log();
    }

#if defined(NDEBUG)

    catch (...)
    {
        ITS_UnknownException unknownExc(__FILE__, __LINE__);

        unknownExc.Log();
    }   

#endif  // defined(NDEBUG)

    // Reached only if an exception has occurred.

    return ITS_NO_SRC;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Entry point.
//

int main(int argc, char* argv[])
{
    cout << endl << "Begin GSM MAP V5 send (with toolkit) example..." << endl;

#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif // defined(WIN32)

    try
    {
        Initialize(argc, argv);

        TIMERS_Sleep(1);

        ITS_ThreadPoolEntry threadPoolEntry;

        for (int i = 0; i < sendCount; i++)
        {
            int res = workerPool->
                    GetFirstAvailThread(threadPoolEntry);
    
            if (res != ITS_SUCCESS)
            {
                ITS_THROW_ERROR(res);
            }

            ITS_Worker* worker = 
                static_cast<ITS_Worker*> (threadPoolEntry.GetThread());

            if (worker == NULL)
            {
                workerPool->ReturnToAvailThreads(threadPoolEntry);

                bool must_not_be_reached = false;

                ITS_ASSERT(must_not_be_reached);

                return EXIT_FAILURE;
            }

            res = workerPool->
                        DispatchOnThread(threadPoolEntry, 
                                         WorkerTcapThreadFunction,
                                         NULL);

            if (res != ITS_SUCCESS)
            {
                workerPool->
                    ReturnToAvailThreads(threadPoolEntry);

                ITS_THROW_ERROR(worker != NULL);
            }

            TIMERS_Sleep(1);
        }

        while (!stopRequested)
        {
            TIMERS_Sleep(1);
        }
        
        Terminate();
        
        // No exception handled.

        cout << endl << "End of GSM MAP V5 send (with toolkit) example." << endl;

        // To stop here in console application.

        cout << endl << "Press Enter to quit...";

        char c = '\0';
        cin.get(c);

        return EXIT_SUCCESS;

    }
    catch (ITS_GenericException& exc)
    {
        exc.Log();
    }
    catch (exception& exc)
    {
        ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);

        standardExc.Log();
    }

#if defined(NDEBUG)

    catch (...)
    {
        ITS_UnknownException unknownExc(__FILE__, __LINE__);

        unknownExc.Log();
    }

#endif // defined(NDEBUG)

    // Reached only if an exception has occurred.

    return EXIT_FAILURE;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//  Following code is identical to test_codec example.
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
//  Utilities.
//

//
//  Macro to get the size (count of items) of a fixed array.
//
#define FixedArraySize(array)       \
    (sizeof(array) / sizeof(array[0]))

//
//  Macro to convert fixed arrays (of bytes) to vectors.
//
#define FixedByteArrayToVector(array)   \
    (vector<byte>(array, array + FixedArraySize(array)))

//
//  Macro to convert fixed arrays (of booleans) to vectors.
//
#define FixedBooleanArrayToVector(array)   \
    (vector<bool>(array, array + FixedArraySize(array)))


////////////////////////////////////////////////////////////////////////////////
//
//  How to Build a GSMMAP Insert Subscriber Data operation argument 
//  (InsertSubscriberDataArg):
//
//  o   Create a InsertSubscriberDataArg object.
//
//  o   Insert data step by step in the created InsertSubscriberDataArg object 
//      (i.e. populate various parameters of the Insert Subscriber Data 
//      operation argument).
//  
//  o   Encode the InsertSubscriberDataArg object to produce a 
//      InsertSubscriberDataArg encoded value.
//

vector<byte> 
BuildOperationInsertSubscriberDataArg()
{
    //  [1] Create a InsertSubscriberDataArg object.

    InsertSubscriberDataArg* insertSubscriberDataArg = 
		                           new InsertSubscriberDataArg();

    ////////////////////////////////////////////////////////////////////////////

    //  Memory management note: all the following parameter objects that are
    //  used to populate the InsertSubscriberDataArg object must be created in 
	//  the heap (i.e. using operator new) and not in the stack. They are 
	//  automatically deleted when the insertSubscriberDataArg object is 
    //  deleted. Only the InsertSubscriberDataArg object itself can be created 
    //  in the stack. 

    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Populate optional parameter "imsi".

    //  [2-1] Create a IMSI object.

    byte fixedArray1[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

    IMSI* imsi = new IMSI(FixedByteArrayToVector(fixedArray1));

    //  [2-2] Set IMSI object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetImsi(imsi);


    ////////////////////////////////////////////////////////////////////////////

    //  [3] Populate optional parameter "msisdn".

    //  [3-1] Create an ISDN_AddressString object.

    byte fixedArray2[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U };

    ISDN_AddressString* iSDN_AddressString = 
        new ISDN_AddressString(FixedByteArrayToVector(fixedArray2));

    //  [3-2] Set ISDN_AddressString object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetMsisdn(iSDN_AddressString);


    ////////////////////////////////////////////////////////////////////////////

    //  [4] Populate optional parameter "category".

    //  [4-1] Create a Category object.

    byte fixedArray3[] = { 0x66U };

    Category* category = 
        new Category(FixedByteArrayToVector(fixedArray3));

    //  [4-2] Set Category object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetCategory(category);


    ////////////////////////////////////////////////////////////////////////////

    //  [5] Populate optional parameter "subscriberStatus".

    //  [5-1] Create a SubscriberStatus object.

    SubscriberStatus* subscriberStatus = new SubscriberStatus();

    subscriberStatus->SetServiceGranted();

    //  [5-2] Set SubscriberStatus object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetSubscriberStatus(subscriberStatus);


    ////////////////////////////////////////////////////////////////////////////

    //  [6] Populate optional parameter "bearerServiceList".

    //  [6-1] Create a BearerServiceList object.

    BearerServiceList* bearerServiceList = new BearerServiceList();

    //  GSM MAP API Note: a BearerServiceList object contains a list of 
    //  Ext_BearerServiceCode objects.

    //  [6-1-1] Create a Ext_BearerServiceCode object.

    byte fixedArray4[] = { 0xAAU };

    Ext_BearerServiceCode* ext_bearerServiceCode1 = 
        new Ext_BearerServiceCode(FixedByteArrayToVector(fixedArray4));

    //  [6-1-2] Create a Ext_BearerServiceCode object.

    byte fixedArray5[] = { 0xBBU };

    Ext_BearerServiceCode* ext_bearerServiceCode2 = 
        new Ext_BearerServiceCode(FixedByteArrayToVector(fixedArray5));

    //  [6-1-3] Add Ext_BearerServiceCode object to BearerServiceList object.

    bearerServiceList->AddElement(ext_bearerServiceCode1);
    
	//  [6-1-4] Add Ext_BearerServiceCode object to BearerServiceList object.

    bearerServiceList->AddElement(ext_bearerServiceCode2);

    //  [6-2] Set BearerServiceList object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetBearerServiceList(bearerServiceList);


    ////////////////////////////////////////////////////////////////////////////

    //  [7] Populate optional parameter "teleserviceList".

    //  [7-1] Create a TeleServiceList object.

    TeleserviceList* teleserviceList = new TeleserviceList();

    //  GSM MAP API Note: a TeleServiceList object contains a list of 
    //  Ext_TeleServiceCode objects.

    //  [7-1-1] Create a Ext_TeleServiceCode object.

    byte fixedArray6[] = { 0xCCU };

    Ext_TeleserviceCode* ext_teleserviceCode1 = 
        new Ext_TeleserviceCode(FixedByteArrayToVector(fixedArray6));

    //  [7-1-2] Create a Ext_TeleServiceCode object.
    
    byte fixedArray7[] = { 0xDDU };

    Ext_TeleserviceCode* ext_teleserviceCode2 = 
        new Ext_TeleserviceCode(FixedByteArrayToVector(fixedArray7));
	
	//  [7-1-3] Create a Ext_TeleServiceCode object.

    byte fixedArray8[] = { 0xEEU };

    Ext_TeleserviceCode* ext_teleserviceCode3 = 
        new Ext_TeleserviceCode(FixedByteArrayToVector(fixedArray8));
	
	//  [7-1-4] Add Ext_TeleServiceCode object to TeleServiceList object.
	
    teleserviceList->AddElement(ext_teleserviceCode1);

	//  [7-1-5] Add Ext_TeleServiceCode object to TeleServiceList object.
	
    teleserviceList->AddElement(ext_teleserviceCode2);

	//  [7-1-6] Add Ext_TeleServiceCode object to TeleServiceList object.

    teleserviceList->AddElement(ext_teleserviceCode3);

    //  [7-2] Set TeleServiceList object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetTeleserviceList(teleserviceList);


    ////////////////////////////////////////////////////////////////////////////

    //  [8] Populate optional parameter "provisionedSS".

    //  [8-1] Create a Ext_SS_InfoList object.

    Ext_SS_InfoList* ext_SS_InfoList = new Ext_SS_InfoList();

    //  GSM MAP API Note: a Ext_SS_InfoList object contains a list of 
    //  Ext_SS_Info objects.

    //  [8-1-1] Create a Ext_SS_Info object.
    
	Ext_SS_Info* ext_SS_Info1 = new Ext_SS_Info();
    
	//  GSM MAP API Note: a Ext-SS-Info object contains a choice of
	//  Ext-ForwInfo, Ext-CallBarInfo, CUG-Info, Ext-SS-Data or EMLPP-Info.

    //  First element choice is forwardingInfo (type Ext_ForwInfo).

    //  [8-1-1-1] Create a Ext_ForwInfo object.

    Ext_ForwInfo* ext_forwInfo = new Ext_ForwInfo();

    //  [8-1-1-1-1] Create a SS_Code object.

    byte fixedArray9[] = { 0x33U };

    SS_Code* sS_Code1 = new SS_Code(FixedByteArrayToVector(fixedArray9));

    //  [8-1-1-1-2] Set the SS_Code object in the Ext_ForwInfo object.

    ext_forwInfo->SetSs_Code(sS_Code1);

    //  [8-1-1-1-3] Create a Ext_ForwFeatureList object.

    Ext_ForwFeatureList* ext_forwFeatureList = 
        new Ext_ForwFeatureList();

	//  GSM MAP API Note: a Ext-SS-Ext_ForwFeatureList object contains a list
	//  of Ext_ForwFeature objects.

    //  [8-1-1-1-3-1] Create a Ext_ForwFeature object.

    Ext_ForwFeature* ext_forwFeature = new Ext_ForwFeature();
    
	//  [8-1-1-1-3-1-1] Create a Ext_SS_Status object.
    
	byte fixedArray10[] = { 0x22U, 0x22U, 0x22U };

    Ext_SS_Status* ext_SS_Status1 = 
        new Ext_SS_Status(FixedByteArrayToVector(fixedArray10));

    //  [8-1-1-1-3-1-2] Create a Ext_BasicServiceCode object.
    
	Ext_BasicServiceCode* ext_basicServiceCode = new Ext_BasicServiceCode();

    byte fixedArray11[] = { 0x44U };

    Ext_BearerServiceCode* ext_bearerServiceCode = 
        new Ext_BearerServiceCode(FixedByteArrayToVector(fixedArray11));

    ext_basicServiceCode->SetChoiceExt_BearerService(ext_bearerServiceCode);

    //  [8-1-1-1-3-1-3] Create a ISDN_SubaddressString object.
    
	byte fixedArray12[] = 
        { 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U };

    ISDN_SubaddressString* iSDN_SubaddressString = 
        new ISDN_SubaddressString(FixedByteArrayToVector(fixedArray12));
    
	//  [8-1-1-1-3-1-4] Set the Ext_SS_Status object in the Ext_ForwFeature 
    //  object.
    
	ext_forwFeature->SetSs_Status(ext_SS_Status1);
    
	//  [8-1-1-1-3-1-5] Set the Ext_BearerServiceCode object in the 
    //  Ext_ForwFeature object.
    
	ext_forwFeature->SetBasicService(ext_basicServiceCode);
    
	//  [8-1-1-1-3-1-6] Set the ISDN_SubaddressString object in the 
    //  Ext_ForwFeature object.
    
	ext_forwFeature->SetForwardedToSubaddress(iSDN_SubaddressString);


    //  [8-1-1-1-3-2] Add the Ext_ForwFeature object to the Ext_ForwFeatureList 
    //  object.

    ext_forwFeatureList->AddElement(ext_forwFeature);

    //  [8-1-1-1-4] Set the ForwardingFeatureList object in the Ext_ForwInfo 
    //  object.

    ext_forwInfo->SetForwardingFeatureList(ext_forwFeatureList);

    //  [8-1-1-2] Set the Choice ForwardingInfo of the Ext_SS_Info object.

    ext_SS_Info1->SetChoiceForwardingInfo(ext_forwInfo);
    
	//  [8-1-2] Create a Ext_SS_Info object.
    
	Ext_SS_Info* ext_SS_Info2 = new Ext_SS_Info();

	//  GSM MAP API Note: a Ext-SS-Info object contains a choice of
	//  Ext-ForwInfo, Ext-CallBarInfo, CUG-Info, Ext-SS-Data or EMLPP-Info.

    // Second element choice is cug-Info.

    //  [8-1-2-1] Create a CUG_Info object.

    CUG_Info* cUG_Info = new CUG_Info();

    //  [8-1-2-1-1] Create a CUG_SubscriptionList object.

    CUG_SubscriptionList* cUG_SubscriptionList = new CUG_SubscriptionList();

	//  GSM MAP API Note: a CUG_SubscriptionList object contains a list of 
    //  CUG_Subscription objects.

    //  [8-1-2-1-1-1] Create a CUG_Subscription object.
    
	CUG_Subscription* cUG_Subscription1 = new CUG_Subscription();

    CUG_Index* cUG_Index1 = new CUG_Index(1999l);

    cUG_Subscription1->SetCug_Index(cUG_Index1);

    byte fixedArray13[] = { 0x11U, 0x22U, 0x33U, 0x44U };

    CUG_Interlock* cUG_Interlock1 = 
        new CUG_Interlock(FixedByteArrayToVector(fixedArray13));

    cUG_Subscription1->SetCug_Interlock(cUG_Interlock1);

    IntraCUG_Options* intraCUG_Options1 = new IntraCUG_Options();

    intraCUG_Options1->SetNoCUG_Restrictions();

    cUG_Subscription1->SetIntraCUG_Options(intraCUG_Options1);

    //  [8-1-2-1-1-2] Create a CUG_Subscription object.
    
	CUG_Subscription* cUG_Subscription2 = new CUG_Subscription();

    CUG_Index* cUG_Index2 = new CUG_Index(2001l);

    cUG_Subscription2->SetCug_Index(cUG_Index2);

    byte fixedArray14[] = { 0x44U, 0x33U, 0x22U, 0x11U };

    CUG_Interlock* cUG_Interlock2 = 
        new CUG_Interlock(FixedByteArrayToVector(fixedArray14));

    cUG_Subscription2->SetCug_Interlock(cUG_Interlock2);

    IntraCUG_Options* intraCUG_Options2 = new IntraCUG_Options();

    intraCUG_Options2->SetNoCUG_Restrictions();

    cUG_Subscription2->SetIntraCUG_Options(intraCUG_Options2);

    //  [8-1-2-1-1-3] Add the CUG_Subscription object to the 
    //  CUG_SubscriptionList object.
    
	cUG_SubscriptionList->AddElement(cUG_Subscription1);
    
	//  [8-1-2-1-1-4] Add the CUG_Subscription object to the 
    //  CUG_SubscriptionList object.

    cUG_SubscriptionList->AddElement(cUG_Subscription2);


    //  [8-1-2-1-2] Set the CUG_SubscriptionList object in the object CUG_Info.

    cUG_Info->SetCug_SubscriptionList(cUG_SubscriptionList);

    //  [8-1-2-2] Set the Choice CUG_Info in the object Ext_SS_Info.

    ext_SS_Info2->SetChoiceCug_Info(cUG_Info);

    //  [8-1-3] Create a Ext_SS_Info object.
    
	Ext_SS_Info* ext_SS_Info3 = new Ext_SS_Info();

	//  GSM MAP API Note: a Ext-SS-Info object contains a choice of
	//  Ext-ForwInfo, Ext-CallBarInfo, CUG-Info, Ext-SS-Data or EMLPP-Info.

    // Third element choice is ss-Data.

    //  [8-1-3-1] Create a Ext_SS_Data object.

    Ext_SS_Data* ext_SS_Data = new Ext_SS_Data();

    //  [8-1-3-1-1] Create a SS_Code object.
    
	byte fixedArray15[] = { 0x11U };

    SS_Code* sS_Code2 = new SS_Code(FixedByteArrayToVector(fixedArray15));
    
	//  [8-1-3-1-2] Create a SS_Status object.
    
	byte fixedArray16[] = { 0x22U, 0x22U };

    Ext_SS_Status* ext_SS_Status2 = 
        new Ext_SS_Status(FixedByteArrayToVector(fixedArray16));

    //  [8-1-3-1-3] Create a SS_SubscriptionOption object.
    
	SS_SubscriptionOption* sS_SubscriptionOption = new SS_SubscriptionOption();

    CliRestrictionOption* cliRestrictionOption = new CliRestrictionOption();

    cliRestrictionOption->SetTemporaryDefaultRestricted();

    sS_SubscriptionOption->SetChoiceCliRestrictionOption(cliRestrictionOption);

	//  [8-1-3-1-4] Set the SS_Code object in the Ext_SS_Data object.

    ext_SS_Data->SetSs_Code(sS_Code2);
	
	//  [8-1-3-1-5] Set the SS_Status object in the Ext_SS_Data object.
    
	ext_SS_Data->SetSs_Status(ext_SS_Status2);
	
	//  [8-1-3-1-6] Set the SS_SubscriptionOption object in the Ext_SS_Data 
    //  object.
    
	ext_SS_Data->SetSs_SubscriptionOption(sS_SubscriptionOption);

    
	//  [8-1-3-2] Set the choice Ext_SS_Data in the Ext_SS_Info object.

    ext_SS_Info3->SetChoiceSs_Data(ext_SS_Data);

	//  [8-1-4] Add Ext_SS_Info object to Ext_SS_InfoList object.
    
	ext_SS_InfoList->AddElement(ext_SS_Info1);
	
	//  [8-1-5] Add Ext_SS_Info object to Ext_SS_InfoList object.
    
	ext_SS_InfoList->AddElement(ext_SS_Info2);
	
	//  [8-1-6] Add Ext_SS_Info object to Ext_SS_InfoList object.
    
	ext_SS_InfoList->AddElement(ext_SS_Info3);
    
	//  [8-2] Set Ext_SS_InfoList object in InsertSubscriberDataArg object.
    
	insertSubscriberDataArg->SetProvisionedSS(ext_SS_InfoList);

    ////////////////////////////////////////////////////////////////////////////

    //  [9] Populate optional parameter "odb_data".

    //  [9-1] Create an ODB_Data object.
    
	ODB_Data* oDB_Data = new ODB_Data();
    
	//  [9-1-1] Create an ODB_GeneralData object.
    
	bool fixedArray17[] = { true, false, true, false, true,
                            false, true, false, true, false,
                            true, false, true, false, true,
                            false, true, false, true, false,
                            true, false, true, false, true };

    ODB_GeneralData* oDB_GeneralData = 
        new ODB_GeneralData(FixedBooleanArrayToVector(fixedArray17));

    //  [9-1-2] Create an ODB_HPLMN_Data object.
    
	bool fixedArray18[] = { false, true, false, true };

    ODB_HPLMN_Data* oDB_HPLMN_Data = 
        new ODB_HPLMN_Data(FixedBooleanArrayToVector(fixedArray18));

    //  [9-1-3] Set the ODB_GeneralData object in the ODB_Data object.
    
	oDB_Data->SetOdb_GeneralData(oDB_GeneralData);
    
	//  [9-1-4] Set the ODB_HPLMN_Data object in the ODB_Data object.

    oDB_Data->SetOdb_HPLMN_Data(oDB_HPLMN_Data);	

    //  [9-2] Set the ODB_Data object in the InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetOdb_Data(oDB_Data);


    ////////////////////////////////////////////////////////////////////////////

    //  [10] Encode InsertSubscriberDataArg object.

    Octets* octets = NULL;

    try
    {
        //  Can throw and AsnEncodeError execption. 

        octets = insertSubscriberDataArg->Encode();
    }
    catch (AsnEncodeError& encodeError)
    {
        cout << endl << encodeError.GetDescription() << endl;

        //  More specific error processing should be added here.

        //  By default re-throw exception.

        throw encodeError;
    }

    cout << endl;
    cout << "Printing InsertSubscriberDataArg ASN.1 encoded value..." << endl;
    cout << *octets;
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////

    //  [11] Retrieve InsertSubscriberDataArg ASN.1 encoded value from octets 
    //  object.

    vector<byte> encodedInsertSubscriberDataArg = octets->GetArray();

    ////////////////////////////////////////////////////////////////////////////

    //  [12] Free all memory allocated on the heap.

    //  [12-1] Delete InsertSubscriberDataArg object (and therefore all the 
    //  parameter objects that have been previously set).

    delete insertSubscriberDataArg;

    //  [12-2] Delete Octets object created by the call to Encode.

    delete octets;

    ////////////////////////////////////////////////////////////////////////////

    //  [13] Return (by value) InsertSubscriberDataArg ASN.1 encoded value.

    return encodedInsertSubscriberDataArg;
}


