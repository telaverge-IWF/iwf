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
 *  ID: $Id: test.cpp,v 9.1 2005/03/23 12:55:28 cvsadmin Exp $
 *
 * LOG: $Log: test.cpp,v $
 * LOG: Revision 9.1  2005/03/23 12:55:28  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:41  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:41  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:52  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.2  2001/10/24 14:36:11  ngoel
 * LOG: add commands
 * LOG:
 * LOG: Revision 1.1  2001/10/23 20:18:07  ngoel
 * LOG: test program
 * LOG:
 ****************************************************************************/

/*
 * list handling routines
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(unix)
#include <unistd.h>
#include <signal.h>
#endif

#include <exception>
#if !defined(HPUX)
#include <iostream>
#else
#include <iostream/iostream.h>
#endif
#include <its.h>
#include <its++.h>

#if !defined(WIN32)
#include <signal.h>
#endif // defined(WIN32)

#include <iostream>

#include <its_app.h>
#include <its_transports.h>
#include <its_thread.h>
#include <its_thread_pool.h>
#include <its_worker.h>
#include <its_semaphore.h>
#include <its_object.h>
#include <its_timers.h>
#include <its_imal_trans.h>

#include <itu/sccp.h>
#include <its_intern.h>
#include <mtp2_cmn.h>
#include <mtp2_sn.h>
#include <its_statics.cpp>


using namespace std;
using namespace its;

class WorkerPool;
////////////////////////////////////////////////////////////////////////////////
//
//  Global variables.
//

static WorkerPool *workerPool;
static int workerPoolSize = 16;
typedef void (*DispatchFunction)(class its::ITS_ThreadPoolThread *, void *);
ITS_HANDLE mtp2Handle;
ITS_Worker* trout;
extern "C" ITS_Class itsADAX_Class;

enum {

    // Worker pool.

    WORKER_POOL_START_INSTANCE      = 10,

    WORKER_POOL_MINIMUM_SIZE        = 16,
    WORKER_POOL_MAXIMUM_SIZE        = 1024
};


void Terminate();

//

//
// local subsystem for testing
//
static void exitHandler(int sig)
{
    ITS_GlobalStop();

    exit(0);

#if defined(WIN32)
    return 1;
#endif
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

    //cout << "Message#4";
    //cout << "ITS_WORKER has been invoked ..." << endl;
    //cout << "Before ITS_ENSURE..." << endl;

    ITS_ENSURE(result != NULL);

    //cout << "After ITS_ENSURE..." << endl;

    return (ITS_ThreadPoolThread *)result;
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
    cout << "Inside Method Terminate ..." << endl;
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

            //
            // Wait for activity to cease.
            //

            ITS_ThreadPool::WaitForDeletionComplete();
   
        ////////////////////////////////////////////////////////////////////////
        //
        //  IntelliSS7 termination.
        //

        ITS_GlobalStop();

        ////////////////////////////////////////////////////////////////////////
        //
        //  Using IntelliSS7 stack (remove feature).
        //

    }
    catch (ITS_GenericException& exp)
    {
        cout << "GetDescription 2 to be executed...";
        cout << endl << exp.GetDescription() << endl;

        ITS_GlobalStop();

        exit(EXIT_FAILURE);
    }

}

int
CreateWorkerAndDispatch(DispatchFunction func)
{
    ITS_ThreadPoolEntry threadPoolEntry;

    int res = 0;

    cout << "Inside CreateWorkerAndDispatch..." << endl;

    if (workerPool!=NULL)
    {
        res = workerPool->GetFirstAvailThread(threadPoolEntry);
    }
    else
    {
        Terminate();
    }

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    ITS_Worker* worker = 
        static_cast<ITS_Worker*> (threadPoolEntry.GetThread());

    if (worker == NULL)
    {
        workerPool->ReturnToAvailThreads(threadPoolEntry);

        return !ITS_SUCCESS;
    }

    res = workerPool->
                DispatchOnThread(threadPoolEntry, 
                                 func,
                                 NULL);

    if (res != ITS_SUCCESS)
    {
        workerPool->
            ReturnToAvailThreads(threadPoolEntry);

        return res;
    }

    return ITS_SUCCESS;
}

/*___________________________________________________________*/
extern "C"
{
ITS_SS7_HANDLE
SS7_Initialize(ITS_UINT mask, ITS_USHORT instance);
int
SS7_GetNextEvent(ITS_SS7_HANDLE handle, ITS_EVENT *event);
int
SS7_PutEvent(ITS_SS7_HANDLE handle, ITS_EVENT *event);


}


void
Mtp3ThreadFunction(its::ITS_ThreadPoolThread* thr, void* arg)
{
    ITS_Event ev;
    ITS_EVENT event;
    for(;;)
    {
            trout->GetNextEvent(ev);
            event = ev.GetEvent();
            switch(event.data[0])
            {
                case L2_L3_IN_SERVICE :
                    printf("APP RECEIVED IN SERVICE\n");
                break;
                case L2_L3_REMOTE_PROCESSOR_OUT :
                    printf("APP RECEIVED PROCESSOR OUTAGE\n");
                break;
                case L2_L3_OUT_OF_SERVICE :
                    printf("APP RECEIVED OUT OF SERVICE\n");
                break;
                case L2_L3_REMOTE_PROCESSOR_REC :
                    printf("APP RECEIVED REMOTE PROCESSOR OUTAGE\n");
                break;
                case L2_L3_DATA :
                    printf("APP RECEIVED DATA\n");
                break;
                case L2_L3_BSNT :
                    printf("APP RECEIVED BSNT\n");
                break;
                case L2_L3_BSNT_NOT_RETRIEVABLE :
                    printf("APP RECEIVED IN BSNT NOT RETRIEVABLE\n");
                break;
                case L2_L3_RETRIEVED_MSG :
                    printf("APP RECEIVED RETRIVED NSG\n");
                break;
                case L2_L3_RETRIEVAL_COMPLETE :
                    printf("APP RECEIVED RETRIEVAL COMPLETE\n");
                break;
                case L2_L3_RETRIEVAL_NOT_POSSIBLE :
                    printf("APP RECEIVED RETRIEVAL NOT POSSIBLE\n");
                break;
                case L2_L3_RB_CLEARED :
                    printf("APP RECEIVED RB CLEARED\n");
                break;
                case L2_L3_RTB_CLEARED :
                    printf("APP RECEIVED RTB CLEARED\n");
                break;
                case L2_L3_CONGESTION_ONSET :
                    printf("APP RECEIVED CONGESTION ONSET\n");
                break;
                case L2_L3_CONGESTION_ABATES :
                    printf("APP RECEIVED CONGESTION ABATES\n");
                break;
                case L2_L3_CONGESTION_DANGER :
                    printf("APP RECEIVED CONGESTION DANGER\n");
                break;
                default :
                    printf("APP RECEIVED INVALID MESSAGE \n");
                break;
            }
    }
}

//
//
// and the entry point.
//
int
main(int argc, char **argv)
{
    ITS_SS7_HANDLE handle;
    ITS_EVENT      event, event1;
    ITS_SS7_CONTEXT *context;
    int fsnc;

    printf("Program: %s\n", argv[0]);

    APPL_SetName("Test");

    ITS_AddFeature(itsADAX_Class);

    ITS_GlobalStart(0);

    trout = new ITS_Worker(0, "User 2", 1,
                          ITS_MTP2|ITS_TRANSPORT_SS7|
                           ITS_TRANSPORT_DELAY_CREATE);

    handle = ITS_Initialize(trout->GetMask(), trout->GetInstance());
    // handle = SS7_Initialize(ITS_MTP2, 1);
    mtp2Handle = handle;

    
    workerPool = new WorkerPool(workerPoolSize);
    workerPool->CreatePool(workerPool->GetSize(), 0);

    CreateWorkerAndDispatch(Mtp3ThreadFunction);

    context = (ITS_SS7_CONTEXT *)handle;


    for(;;)
    {
        char c;

        ITS_EVENT_INIT(&event, ITS_MTP2_ANSI_SRC,
                       105 + 3 * sizeof(ITS_OCTET));

        sleep(1);

        printf(" You want to write (w)->");

        c = getchar();

        fflush(stdin);

        printf("\n");
        if ( c != 'w')
        {
            continue;
        }
        else
        {
            printf("Enter input command command \n");

            printf("Get BSNT (b):\n");

            printf("Retrieve Messages (r):\n");

            printf("Send Data (d):\n");

            printf("MTP2 Start (s):\n");

            printf("MTP2 Stop (e):\n");

            printf("->");

            c = getchar();

            fflush(stdin);

            printf("\n");

            switch(c)
            {
                case 'd' :
                    event.data[0] = L3_L2_DATA;
                    event.data[3] = 1;
                    event.data[4] = 2;
                    event.data[5] = 3;
                    event.data[6] = 4;
                    event.data[7] = 5;
                break;
                case 'b' :
                    event.data[0] = L3_L2_RETRIEVE_BSNT;
                break;
                case 's' :
                    event.data[0] = L3_L2_START;
                break;
                case 'e' :
                    event.data[0] = L3_L2_STOP;
                break;
                case 'r' :
                    event.data[0] = L3_L2_RETRIEVE_MSGS;
                    printf("Please Enter FSNC ->");
                    fflush(stdin);
                    scanf("%d", &fsnc);
                    fflush(stdin);
                    printf("\n");
                    event.data[3] = (ITS_OCTET)fsnc;
                break;
                default :
                    printf("Invalid Entry \n");
                break;
                 
            }
            TRANSPORT_PutEvent(trout->GetInstance(), &event);
        }
    }


}
