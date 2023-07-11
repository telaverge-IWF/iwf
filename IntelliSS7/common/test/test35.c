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
 *  ID: $Id: test35.c,v 9.1 2005/03/23 12:53:52 cvsadmin Exp $
 *
 * LOG: $Log: test35.c,v $
 * LOG: Revision 9.1  2005/03/23 12:53:52  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:33  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/10/28 22:07:39  mmiers
 * LOG: Update tests, add WorkItem test.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <its.h>
#include <its_work_item.h>
#include <its_worker.h>
#include <its_ip_trans.h>
#include <its_fifo_trans.h>
#include <its_gfifo_trans.h>
#include <its_tq_trans.h>
#include <its_ss7_trans.h>
#include <its_service.h>
#include <its_timers.h>

#if defined(ANSI)
#include <ansi/tcap.h>
#define USE_STACK   ISS7_ANSI_Stack
#elif defined(CCITT)
#include <itu/tcap.h>
#define USE_STACK   ISS7_CCITT_Stack
#elif defined(PRC)
#include <china/tcap.h>
#define USE_STACK   ISS7_PRC_Stack
#else
#error "Protocol family not defined"
#endif

/*
 * a simple class for this test.
 */
typedef struct
{
    TPOOL*  pool;
    int     count;
}
LocalPool;

#define FIRST_BORDER    1

/*
 * two pools. One is the worker pool, the other is the border pool
 */
static LocalPool   borderPool;

/*
 * Create one thread in the border pool
 */
TPOOL_THREAD *
CreateBorderPoolThread(TPOOL* pool, int stackSize)
{
    LocalPool* p = (LocalPool *)TPOOL_USER_DATA(pool);
    WORKER_Control *worker;

    switch (p->count)
    {
    case 1:
        worker = WORKER_InitWorker(stackSize, "Border0", (ITS_USHORT)p->count,
                                   ITS_SCCP|ITS_TRANSPORT_SSOCKET|
                                   ITS_TRANSPORT_DELAY_CREATE);
        break;

    case 2:
        worker = WORKER_InitWorker(stackSize, "Border1", (ITS_USHORT)p->count,
                                   ITS_SCCP|ITS_TRANSPORT_SSOCKET|
                                   ITS_TRANSPORT_DELAY_CREATE);
        break;

    default:
        printf("Tried to create more threads than we understand here.\n");
        return (NULL);
    }

    p->count++;

    return ((TPOOL_THREAD *)worker);
}

/*
 * standard border loop
 */
void
BorderDispatch(TPOOL_THREAD* thr, void *arg)
{
    WORKER_Control* work = (WORKER_Control *)thr;
    ITS_HANDLE h;
    ITS_EVENT event;

    /*
     * getting NULL here is a fatal error
     */
    assert((h = ITS_Initialize(WORKER_MASK(work),
                               WORKER_INSTANCE(work))) != NULL);
    
    /*
     * dispatcher loop.  Take all incoming messages and send them to SCCP.
     */
    while (!TPOOL_THREAD_EXIT(work))
    {
        /*
         * Note: we could use ITS_GetNextEvent() here.
         */
        if (WORKER_GetNextEvent(work, &event) != ITS_SUCCESS)
        {
            continue;
        }

        /*
         * border transports implement MTP3.
         */
        event.src = ITS_MTP3_SRC;

        /*
         * this example is only handling SCCP messages.  ISUP would
         * be handled similarly.
         */
        if (TRANSPORT_PutEvent(ITS_SCCP_SRC, &event) != ITS_SUCCESS)
        {
            printf("Couldn't send SCCP message to TCAP\n");
        }
    }
    
    /*
     * this is good practice
     */
    ITS_Terminate(h);
}

/***************************************************************************
 *  Purpose:
 *      This function represents a TCAP "unit-of-work", or transaction handler
 *
 *  Input Parameters:
 *      thr - a pointer to an ITS_Worker thread
 *      arg - the argument to this function execution session
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
 ***************************************************************************/
void
HandleInvoke(TPOOL_THREAD *s, void *arg)
{
    WORKER_Control* self = (WORKER_Control*)s;
    ITS_HANDLE hd;
    ITS_EVENT ev;
    TCAP_DLG dlg;
    TCAP_CPT cpt;
    ITS_HDR hdr;

    /*
     * getting NULL here is a fatal error
     */
    assert((hd = ITS_Initialize(WORKER_MASK(self),
                                WORKER_INSTANCE(self))) != NULL);
    
    /*
     * Get the Dialog portion of the TCAP message
     */
    WORKER_GetNextEvent(self, &ev);

    /*
     * bail if the event is not a dialogue
     */
    assert(TCAP_MSG_TYPE(&ev) == ITS_TCAP_DLG);
    TCAP_ReceiveDialogue(USE_STACK, &ev, &hdr, &dlg);
    
    /*
     * Get the component portion of the TCAP message
     */
    WORKER_GetNextEvent(self, &ev);

    /*
     * make sure we got a component
     */
    assert(TCAP_MSG_TYPE(&ev) == ITS_TCAP_CPT);
    TCAP_ReceiveComponent(USE_STACK, &ev, &hdr, &cpt);

    /*
     * handle invokes
     */
    if (cpt.ptype == TCPPT_TC_INVOKE)
    {
        ITS_BOOLEAN isNat;
        ITS_OCTET family, op;

        /* byte two is just the length */
        isNat = cpt.u.invoke.operation.data[0] == TCPPN_OCI_NATIONAL_TCAP;
        family =  cpt.u.invoke.operation.data[2];
        op =  cpt.u.invoke.operation.data[3];

        /*
         * what to do for each operation
         */
        switch(op)
        {
        case 1:
            /* yadadayadada */
            break;

        default:
            break;
        }
     }
     else 
     {
         /* if it's not an invoke, it's an application error */
         assert(ITS_FALSE);
     }
}

/***************************************************************************
 *  Purpose:
 *      Routes the TCAP message to the application based on the dialog id
 *      This functions as the "application selector" as documented by
 *      ITS_RoutingMap
 *
 *  Input Parameters:
 *      hdr - the per-thread application context (dialogue_id).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      returns the instance id of the first available dispatch thread
 *
 *  Notes:
 * WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
 *
 *   DO NOT THROW EXCEPTIONS FROM THIS CALL.  THE CALLER IS A "C" FUNCTION
 *   THAT HAS A LOCKED MUTEX.  AN UNCAUGHT EXCEPTION ORIGINATING FROM THIS
 *   FUNCTION MEANS THE MUTEX WILL STAY LOCKED, EFFECTIVELY BLOCKING ANY NEW
 *   TCAP TRANSACTION OR SCCP CONNECTION FROM THE PROGRAM.  YOU HAVE BEEN
 *   WARNED.
 *
 *   IN THE "C" EXAMPLE, THIS WARNING WOULD APPLY TO longjmp() -ing out of
 *   THIS FUNCTION.  WHICH IS WHAT AN EXCEPTION IS.  Um.  Sorry.  Soapbox.
 *
 * WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
 *
 *
 *  See Also:
 ***************************************************************************/
ITS_USHORT
SelectApplication(ITS_HDR *hdr, ITS_EVENT* event)
{
    TPOOL_THREAD* iThread;
    WORKER_Control* work;
    ITS_USHORT qid;
    int did;
    
    did = hdr->context.dialogue_id;

    return (ITS_INVALID_SRC);
}

/*
 * initialization function
 */
void
InitFunc(int argc, const char **argv)
{
    /*
     * initialize infrastructure first.
     */
    if (ITS_GlobalStart(ITS_SCCP|ITS_TCAP) != ITS_SUCCESS)
    {
        printf("Couldn't start IntelliSS7\n");

        SERVICE_CallHandler(SERV_HANDLER_STOP);

        return;
    }

    /*
     * set the application selector for TCAP messages
     */
    assert(ROUTE_SetApplicationSelector(SelectApplication) != NULL);

    /*
     * Now that that's done, create the border pool
     */
    borderPool.count = FIRST_BORDER;

    if ((borderPool.pool = TPOOL_InitPool(&borderPool)) == NULL)
    {
        printf("Couldn't initialize the thread pool\n");

        SERVICE_CallHandler(SERV_HANDLER_STOP);

        return;
    }

    if (TPOOL_CreatePool(borderPool.pool, 2, 0,
                         CreateBorderPoolThread) != ITS_SUCCESS)
    {
        printf("Couldn't create worker pool.\n");

        SERVICE_CallHandler(SERV_HANDLER_STOP);

        return;
    }

    /*
     * start the border dispatchers.
     */
    TPOOL_Dispatch(borderPool.pool, BorderDispatch, NULL);
    TPOOL_Dispatch(borderPool.pool, BorderDispatch, NULL);
}

void
MainFunc(void)
{
    TIMERS_Sleep(1);
}

void
TermFunc(void)
{
    TPOOL_DestroyPool(borderPool.pool);

    ITS_GlobalStop();
}

/*
 * application entry point
 */
int
main(int argc, char **argv)
{
    if (SERVICE_Initialize(argv[0], argv[0], NULL) != ITS_SUCCESS)
    {
        printf("Can't initialize service.\n");

        return (EXIT_FAILURE);
    }

    SERVICE_SetInitFunction(InitFunc);
    SERVICE_SetMainFunction(MainFunc);
    SERVICE_SetTermFunction(TermFunc);

    SERVICE_ProcessCommandLine(argc, (const char **)argv);

    if (SERVICE_GetType() == ST_SERVICE)
    {
        SERVICE_RunAsService();
    }
    else if (SERVICE_GetType() == ST_CONSOLE_APPLICATION)
    {
        SERVICE_RunAsConsoleApplication(argc, (const char **)argv);
    }

    SERVICE_Terminate();

    return SERVICE_GetExitCode();
}
