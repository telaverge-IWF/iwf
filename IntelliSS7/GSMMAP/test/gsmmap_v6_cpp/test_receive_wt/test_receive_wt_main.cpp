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
//  ID: $Id: test_receive_wt_main.cpp,v 9.1 2005/03/23 12:51:41 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  GSM MAP v6 receive (with toolkit) example.
//
//  This example shows how to receive the argument of an GSM MAP Insert Subscriber Data operation.
//  The part used to interpret (decode and retrieve data) for the Insert Subscriber Data 
//  operation argument is identical to the test_codec example.
//  This example uses the IntelliNet toolkit to demonstrate its routing
//  capabilities to a specific worker thread, based on the dialogue id.
//
//

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
#include <map_v6_insert_subscriber_data_arg.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace map_common;
using namespace map_v6;
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
void InterpretOperationInsertSubscriberDataArg(const vector<byte>& 
                                               encodedInsertSubscriberDataArg);


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
                                ITS_TRANSPORT_SSOCKET       |
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

        ITS_Application::SetName("test_receive_wt");


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
        //  Receive (infinite) loop:
        //
        //  o   Receive TCAP begin dialogue.
        //
        //  o   Receive TCAP invoke component.
        //
        //  o   Call function to interpret GSM MAP Insert Subscriber Data operation argument.
        //
        //  o   Send back a TCAP continue dialogue if last component.
        //
        //  o   Exit loop.
        //

        TCAP_Dialogue* recvDlg       = NULL;
        TCAP_Component* recvCpt      = NULL;
        ITS_USHORT currentDialogueID = 0;

	    while (true)
	    {
            ITS_Event event;

            int res = worker->GetNextEvent(event);

            if (res != ITS_SUCCESS)
            {
                ITS_Error itsError(res, __FILE__, __LINE__);

                cout << endl << "Thread(" << 
                        WORKER_NUMBER(worker->GetInstance()) << 
                        ")" << itsError.GetDescription() << endl;

                continue;
            }

            cout << endl << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << 
                    ")" <<"Received Event..." << endl;

            cout << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")" <<
                    "Source: <" << event.GetSource() << ">." << endl;

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

                cout << endl << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")" <<
                        "Receive TCAP component..." << endl;

                switch (recvCpt->GetComponentType())
                {
                case TCAP_PT_TC_INVOKE_CCITT:
                {
                    cout << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")" <<
                            "Invoke component." << endl;

                    TCAP_Invoke* recvInvokeCpt = 
                        static_cast<TCAP_Invoke*> (recvCpt);

                    ITS_LONG operation = 0;

                    recvInvokeCpt->GetOperation(operation);

                    // Selection according to GSM MAP operation.

                    switch (operation)
                    {
                    case OP_insertSubscriberData:
                    {
                        vector<byte> encodedInsertSubscriberDataArg;

                        // The parameter field of the TCAP invoke component
                        // contains the GSM MAP Insert Subscriber Data operation argument.

                        recvInvokeCpt->GetParameter(encodedInsertSubscriberDataArg);

                    ////////////////////////////////////////////////////////////
                    //
                    //  Function call uses GSM MAP ASN.1 C++ API.
                    //

                        InterpretOperationInsertSubscriberDataArg(encodedInsertSubscriberDataArg);

                    //
                    ////////////////////////////////////////////////////////////

                        break;
                    }

                    default:
                    {
                        // Should be processed by complete code (all other GSM MAP
                        // operation codes).

                        break;
                    }
                    } // Switch.

                    break;
                }

                case TCAP_PT_TC_RESULT_L_CCITT:
                case TCAP_PT_TC_U_ERROR_CCITT:  
                case TCAP_PT_TC_R_REJECT_CCITT: 
                case TCAP_PT_TC_RESULT_NL_CCITT:
                case TCAP_PT_TC_L_CANCEL_CCITT:
                case TCAP_PT_TC_U_CANCEL_CCITT: 
                case TCAP_PT_TC_L_REJECT_CCITT: 
                case TCAP_PT_TC_U_REJECT_CCITT:
                {
                    // Should be processed by complete code.

                    break;
                }

                default:
                {
                    // Should not be reached.

                    break;
                }
                } // Switch. 

                // Last component? Send a Continue Dialog back to the
                // sender.

                if (recvCpt->GetLast())
                {
                    TCAP_Continue continueDlg;

                    continueDlg.SetOPC(0);
                    
                    continueDlg.SetDialogueID(currentDialogueID);
                    
                    TCAP_Dialogue::Send(handle, &continueDlg);
                }
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

                cout << endl << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << 
                        ")" <<"Received TCAP dialogue..." << endl;

                currentDialogueID = recvDlg->GetDialogueID();

                cout << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")" <<
                        "Dialogue ID: <" << currentDialogueID << ">." << endl;

                switch (recvDlg->GetDialogueType())
                {
                case TCAP_PT_TC_BEGIN_CCITT:
                {
                    cout << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")" <<
                            "Begin dialogue." << endl;

                    TCAP_Begin* recvBeginDlg = 
                        static_cast<TCAP_Begin*>(recvDlg);

                    break;
                }

                case TCAP_PT_TC_UNI_CCITT:
                case TCAP_PT_TC_END_CCITT:
                {
                    cout << "Thread(" << WORKER_NUMBER(worker->GetInstance()) << ")" <<
                            "End dialogue." << endl;

                    TCAP_End* recvEndDlg = static_cast<TCAP_End*>(recvDlg);

                    break;
                }
                case TCAP_PT_TC_CONTINUE_CCITT:
                case TCAP_PT_TC_P_ABORT_CCITT:
                case TCAP_PT_TC_U_ABORT_CCITT:
                case TCAP_PT_TC_NOTICE_CCITT:
                {
                    // Should be processed by complete code.

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

        if (recvDlg != NULL)
        {
            delete recvDlg;
            recvDlg = NULL;
        }

        if (recvCpt != NULL)
        {
            delete recvCpt;
            recvCpt = NULL;
        }


        WorkerTcapThreadFunctionTerminate(
                                        handle,
                                        worker,
                                        dlg,
                                        cpt,
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
    cout << endl << "Begin GSM MAP v6 receive (with toolkit) example..." << endl;

#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif // defined(WIN32)

    try
    {
        Initialize(argc, argv);

        while (!stopRequested)
        {
            TIMERS_Sleep(1);
        }
        
        Terminate();
        
        // No exception handled.

        cout << endl << "End of GSM MAP v6 receive (with toolkit) example." << endl;

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
//  How to interpret an (encoded) GSM MAP Insert Subscriber Data operation 
//  argument (InsertSubscriberDataArg):
//
//  o   Decode a InsertSubscriberDataArg encoded value (i.e. create a 
//      InsertSubscriberDataArg object from a InsertSubscriberDataArg encoded 
//      value).
//
//  o   Retrieve Data from a InsertSubscriberDataArg object.
//

void
InterpretOperationInsertSubscriberDataArg(
                            const vector<byte>& encodedInsertSubscriberDataArg)
{
    //  [1] Create an Octets object from the InsertSubscriberDataArg ASN.1 
    //  encoded value.

    Octets* octets = new Octets(encodedInsertSubscriberDataArg);

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Create a InsertSubscriberDataArg object (used by the decode phase).

    InsertSubscriberDataArg* 
        insertSubscriberDataArg = new 
            InsertSubscriberDataArg();

    ////////////////////////////////////////////////////////////////////////////

    //  [3] Decode the InsertSubscriberDataArg ASN.1 encoded value and therefore
    //  populate previously created InsertSubscriberDataArg object.

    try
    {
        //  Can throw and AsnDecodeError exception.

        insertSubscriberDataArg->Decode(*octets);
    }
    catch (AsnDecodeError& decodeError)
    {
        cout << endl << decodeError.GetDescription() << endl;

        // More specific error processing should be added here.

        // By default re-throw exeception.

        throw decodeError;
    }

    cout << endl;
    cout << "Printing decoded InsertSubscriberDataArg object..." << endl;
    cout << *insertSubscriberDataArg;
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////

    //  [4] Retrieve optional parameter "imsi".

    if (insertSubscriberDataArg->OptionImsi())
    {
        //  [4-1] Retrieve reference to IMSI object.

        const IMSI& imsi = insertSubscriberDataArg->GetImsi();
        
		//  [4-2] Retrieve contents of IMSI object.
        
		vector<byte> vector1 = imsi.GetArray();

        //  Do something with vector of bytes...
        
		//  [4-3] Print IMSI object.
        
		cout << endl;
        cout << "Printing IMSI object..." << endl;
        cout << imsi;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [5] Retrieve optional parameter "msisdn".

    if (insertSubscriberDataArg->OptionMsisdn())
    {
        //  [5-1] Retrieve reference to  ISDN_AddressString object.

        const ISDN_AddressString& 
            iSDN_AddressString = 
                insertSubscriberDataArg->GetMsisdn();
        
		//  [5-2] Retrieve contents of ISDN_AddressString object.
        
		vector<byte> vector2 = iSDN_AddressString.GetArray();

        //  Do something with vector of bytes...
        
		//  [5-3] Print ISDN_AddressString object.
        
		cout << endl;
        cout << "Printing ISDN_AddressString object..." << endl;
        cout << iSDN_AddressString;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [6] Retrieve optional parameter "category".

    if (insertSubscriberDataArg->OptionCategory())
    {
        //  [6-1] Retrieve reference to  Category object.

        const Category& category = insertSubscriberDataArg->GetCategory();
        
		//  [6-2] Retrieve contents of Category object.
        
		vector<byte> vector3 = category.GetArray();

        //  Do something with vector of bytes...
        
		//  [6-3] Print Category object.
        
		cout << endl;
        cout << "Printing Category object..." << endl;
        cout << category;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [7] Retrieve optional parameter "subscriberStatus".

    if (insertSubscriberDataArg->OptionSubscriberStatus())
    {
        //  [7-1] Retrieve reference to  SubscriberStatus object.

        const SubscriberStatus& 
            subscriberStatus = 
                insertSubscriberDataArg->GetSubscriberStatus();
        
		//  [7-2] Retrieve contents of SubscriberStatus object.
        
        if (subscriberStatus.IsOperatorDeterminedBarring())
        {
            // Do something...
        }
        else if (subscriberStatus.IsServiceGranted())
        {
            // Do something...
        }
        
		//  [7-3] Print SubscriberStatus object.
        
		cout << endl;
        cout << "Printing SubscriberStatus object..." << endl;
        cout << subscriberStatus;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [8] Retrieve optional parameter "bearerServiceList".

    if (insertSubscriberDataArg->OptionBearerServiceList())
    {
        //  [8-1] Retrieve reference to  BearerServiceList object.

        const BearerServiceList& bearerServiceList =
            insertSubscriberDataArg->GetBearerServiceList();
    
        //  GSM MAP API Note: a BearerServiceList object contains a list of 
        //  Ext_BearerServiceCode objects.

        //  [8-2] Retrieve contents of BearerServiceList object.

        for (int i = 0; i < bearerServiceList.Size(); i++)
        {
            //  [8-2-1] Retrieve reference to Ext_BearerServiceCode object.
            
            const Ext_BearerServiceCode& ext_bearerServiceCode = 
                            bearerServiceList.ElementAt(i);

            //  [8-2-2] Retrieve contents of Ext_BearerServiceCode object.

            vector<byte> vector4 = ext_bearerServiceCode.GetArray();

            //  Do something with vector of bytes...

            //  [8-2-3] Print Ext_BearerServiceCode object.

            cout << endl;
            cout << "Printing Ext_BearerServiceCode object..." << endl;
            cout << ext_bearerServiceCode;
            cout << endl;
        }

        //  [8-3] Print BearerServiceList object.

        cout << endl;
        cout << "Printing BearerServiceList object..." << endl;
        cout << bearerServiceList;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [9] Retrieve optional parameter "provisionedSS".

    if (insertSubscriberDataArg->OptionProvisionedSS())
    {
        //  [9-1] Retrieve reference to  Ext_SS_InfoList object.

        const Ext_SS_InfoList& ext_SS_InfoList = 
            insertSubscriberDataArg->GetProvisionedSS();

        //  GSM MAP API Note: a Ext_SS_InfoList object contains a list of 
        //  Ext_SS_Info objects.

        //  [9-2] Retrieve contents of Ext_SS_InfoList object.

        for (int i = 0; i < ext_SS_InfoList.Size(); i++)
        {
            //  [9-2-1] Retrieve reference to Ext_SS_Info object.
            
            const Ext_SS_Info& ext_SS_Info = 
                            ext_SS_InfoList.ElementAt(i);

	        //  GSM MAP API Note: a Ext-SS-Info object contains a choice of
	        //  Ext-ForwInfo, Ext-CallBarInfo, CUG-Info, Ext-SS-Data or 
            //  EMLPP-Info.

            //  [9-2-2] Retrieve contents of Ext_SS_Info object.
            
            if (ext_SS_Info.ChoiceForwardingInfo())
            {
                //  [9-2-2-1] Retrieve reference to Ext_ForwInfo object.
                
                const Ext_ForwInfo& ext_ForwInfo = 
                            ext_SS_Info.GetChoiceForwardingInfo();                
                
                //  [9-2-2-2] Retrieve contents of Ext_ForwInfo object.
                
                //  [9-2-2-2-1] Retrieve reference to SS_Code object.
                
                const SS_Code& sS_Code = ext_ForwInfo.GetSs_Code();

                //  [9-2-2-2-2] Retrieve contents of SS_Code object.
        
                vector<byte> vector5 = sS_Code.GetArray();

                //  Do something with vector of bytes...
                
                //  [9-2-2-2-3] Print SS_Code object.
                
                cout << endl;
                cout << "Printing SS_Code object..." << endl;
                cout << sS_Code;
                cout << endl;

                //  [9-2-2-2-4] Retrieve reference to Ext_ForwFeatureList 
                //  object.

                const Ext_ForwFeatureList& 
                    ext_ForwFeatureList = 
                        ext_ForwInfo.GetForwardingFeatureList();

                //  [9-2-2-2-5] Retrieve contents of Ext_ForwFeatureList object.
           
	            //  GSM MAP API Note: a Ext_ForwFeatureList object contains a 
                //  list of Ext_ForwFeature objects.

                for (int i = 0; i < ext_ForwFeatureList.Size(); i++)
                {
                    //  [9-2-2-2-5-1] Retrieve reference to Ext_ForwFeature 
                    //  object.
            
                    const Ext_ForwFeature& ext_ForwFeature = 
                                    ext_ForwFeatureList.ElementAt(i);

                    //  [9-2-2-2-5-2] Retrieve contents of Ext_ForwFeature 
                    //  object.
                    
                    //  [9-2-2-2-5-2-1] Retrieve reference to Ext_SS_Status 
                    //  object.
                    
                    const Ext_SS_Status& ext_SS_Status = 
                        ext_ForwFeature.GetSs_Status();

                    //  [9-2-2-2-5-2-2] Retrieve contents of Ext_SS_Status 
                    //  object.

                    vector<byte> vector6 = ext_SS_Status.GetArray();

                    //  Do something with vector of bytes...
                    
                    //  [9-2-2-2-5-2-3] Print Ext_SS_Status object.

                    cout << endl;
                    cout << "Printing Ext_SS_Status object..." << endl;
                    cout << ext_SS_Status;
                    cout << endl;
                    
                    //  [9-2-2-2-5-2-4] Retrieve reference to 
                    //  Ext_BasicServiceCode object.
                    
                    const Ext_BasicServiceCode& ext_BasicServiceCode = 
                                    ext_ForwFeature.GetBasicService();

                    //  [9-2-2-2-5-2-5] Retrieve contents of 
                    //  Ext_BasicServiceCode object.

                    if (ext_BasicServiceCode.ChoiceExt_BearerService())
                    {
                        // Do something...
                    }
                    else if (ext_BasicServiceCode.ChoiceExt_Teleservice())
                    {
                        // Do something...
                    }
                    
                    //  [9-2-2-2-5-2-6] Print Ext_BasicServiceCode object.

                    cout << endl;
                    cout << "Printing Ext_BasicServiceCode object..." << endl;
                    cout << ext_BasicServiceCode;
                    cout << endl;
                    
                    //  [9-2-2-2-5-2-7] Retrieve reference to 
                    //  ISDN_SubaddressString object.
                    
                    const ISDN_SubaddressString& iSDN_SubaddressString =
                                    ext_ForwFeature.GetForwardedToSubaddress();

                    //  [9-2-2-2-5-2-8] Retrieve contents of 
                    //  ISDN_SubaddressString object.

                    vector<byte> vector7 = iSDN_SubaddressString.GetArray();

                    //  Do something with vector of bytes...
                    
                    //  [9-2-2-2-5-2-9] Print ISDN_SubaddressString object.

                    cout << endl;
                    cout << "Printing ISDN_SubaddressString object..." << endl;
                    cout << iSDN_SubaddressString;
                    cout << endl;
                    
                    //  [9-2-2-2-5-3] Print Ext_ForwFeature object.

                    cout << endl;
                    cout << "Printing Ext_ForwFeature object..." << endl;
                    cout << ext_ForwFeature;
                    cout << endl;
                }                
                
                //  [9-2-2-2-6] Print Ext_ForwFeatureList object.

                cout << endl;
                cout << "Printing Ext_ForwFeatureList object..." << endl;
                cout << ext_ForwFeatureList;
                cout << endl;
                
                //  [9-2-2-3] Print Ext_ForwInfo object.

                cout << endl;
                cout << "Printing Ext_ForwInfo object..." << endl;
                cout << ext_ForwInfo;
                cout << endl;
            }
            else if (ext_SS_Info.ChoiceCug_Info())
            {
                cout << endl;
                cout << "Choice Cug Info not printed..." << endl;
                cout << endl;
            }
            else if (ext_SS_Info.ChoiceSs_Data())
            {
                cout << endl;
                cout << "Choice Ss Data not printed..." << endl;
                cout << endl;
            }

            //  [9-2-3] Print Ext_SS_Info object.

            cout << endl;
            cout << "Printing Ext_SS_Info object..." << endl;
            cout << ext_SS_Info;
            cout << endl;
        }

        //  [9-3] Print Ext_SS_InfoList object.

        cout << endl;
        cout << "Printing Ext_SS_InfoList object..." << endl;
        cout << ext_SS_InfoList;
        cout << endl;
    }            

    ////////////////////////////////////////////////////////////////////////////

    //  [10] Free all memory allocated on the heap.

    //  [10-1] Delete Octets object.

    delete octets;

    //  [10-2] Delete InsertSubscriberDataArg object.

    delete insertSubscriberDataArg;
}
