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
 * LOG: $Log: dia_module.h,v $
 * LOG: Revision 3.7.50.1.4.1.8.1  2014/08/26 10:27:38  pramana
 * LOG: Compilation warning fixes in imsdia
 * LOG:
 * LOG: Revision 3.7.50.1.4.1  2013/12/13 09:34:58  vsarath
 * LOG: Merged the session-splict changes
 * LOG:
 * LOG: Revision 3.7.50.1  2013/02/27 08:49:06  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.7  2009/07/13 06:02:49  rajeshak
 * LOG: Reverting back session table changes.
 * LOG:
 * LOG: Revision 3.6  2009/06/29 14:34:09  rajeshak
 * LOG: Changes done for performance enhancement (splitting the session table).
 * LOG:
 * LOG: Revision 3.5  2009/04/10 06:18:43  sureshj
 * LOG: Compilation option HMI_ENABLE removed.
 * LOG:
 * LOG: Revision 3.4  2009/04/07 14:38:47  sureshj
 * LOG: TRANSPORT_IS_ACTIVE handling for HMI monitoring of transport threads.
 * LOG:
 * LOG: Revision 3.3  2009/03/19 08:15:45  nvijikumar
 * LOG: Reverting back HMI changes (App hangs and drop in TPS)
 * LOG: HMI changes are planed to provide after 4.0
 * LOG:
 * LOG: Revision 3.2  2009/03/16 10:41:55  sureshj
 * LOG: FeatureId: Support for Health Monitoring Interface.
 * LOG: Description: HMI monitors Diameter threads.
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:22  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.4  2006/10/05 11:53:11  yranade
 * LOG: ITS-Diameter specific updates. Removed cyclic dependency, move DiaThread
 * LOG: interface into it's own file.
 * LOG:
 * LOG: Revision 2.3  2006/09/26 06:24:03  nvijikumar
 * LOG: Added return statement ( issue with Sun CC Compilation)
 * LOG:
 * LOG: Revision 2.2  2006/09/13 10:08:51  yranade
 * LOG: ITS-Diameter specific updates.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.2  2006/04/07 11:35:46  yranade
 * LOG: DoxyGen Compatible Code Comments.
 * LOG:
 * LOG: Revision 1.1  2006/03/02 13:03:08  tpanda
 * LOG: Building IMS Infrastructure
 * LOG:
 *
 * ID: $Id: dia_module.h,v 3.7.50.1.4.1.8.1 2014/08/26 10:27:38 pramana Exp $
 ****************************************************************************/
#ident "$Id: dia_module.h,v 3.7.50.1.4.1.8.1 2014/08/26 10:27:38 pramana Exp $"

#ifndef DIA_MODULE_H
#define DIA_MODULE_H

#include <its++.h>
#include <its_thread.h>
#include <its_tq_trans.h>
#include <engine++.h>
#include <its_hmi.h>

#include <dia_defines.h>
#include <dia_thread.h>
#include <dia_msghandler.h>

extern LIST_Manager *monList;

class DIAThreadIdList
{
public:
    typedef struct _entry
    {
        int threadId;
        int tqInst;
        int stTblId;
    }Entry;

   static void AddToThreadIdTable(int tqInst)
   {
       int thId = THREAD_GetCurrentThreadID();
       lock.Acquire();
       if (count < MAX_ROUTER_THREADS)
       {
           table[count].threadId = thId;
           table[count].tqInst   = tqInst;
           table[count].stTblId  = SESSION_TABLE_ID + (tqInst - DIASTACK_TQ_INST);
           count++;
       }
       lock.Release();
    }

   static int GetTableId()
   {
       int thId = THREAD_GetCurrentThreadID();
       for(int i=0; i<count; i++)
       {
           if (thId == table[i].threadId)
           {
               return (table[i].stTblId);
           }
       }
        //DT_ERR(("GetTableId: ERROR-Unknown Thread ID -%d\n", thId));
       return 0;
   }

    static int GetTQInstance()
    {
        int thId = THREAD_GetCurrentThreadID();
        for(int i=0; i<count; i++)
        {
            if (thId == table[i].threadId)
            {
                return (table[i].tqInst);
            }
        }
        //DT_ERR(("GetTableId: ERROR-Unknown Thread ID -%d\n", thId));
        return 0;
    }
private:
    static Entry table[MAX_ROUTER_THREADS];
    static int count;
    static its::ITS_Mutex lock;
};

/** DIAWorker 
 *****************************************************************************
 *  Interface:
 *      DIAWorker 
 *      
 *  Purpose:
 *      Provides an interface for application developers to
 *      design a multi-threaded application.Worker is a Thread with
 *      an associated TaskQueue Transport.
 *
 *****************************************************************************/
class DIAWorker:public DIAThread
{
public:
    /***********************************************************************/
    /** Purpose:
    *       Create a dia application specific worker
    *       
    *  Input Parameters:
    *       which - workerId
    *       
    ************************************************************************/
    DIAWorker(int which, bool routerFlag = false)
    :DIAThread(0, true, this)
    {
       _which = which;
       doExit = ITS_FALSE;
       isMsgRouter = routerFlag;
    }
    
    /***********************************************************************/
    /** Purpose:
    *       Destruct a dia application specific thread
    *           
    ************************************************************************/
    virtual ~DIAWorker()
    {
    }    

    /***********************************************************************/
    /** Purpose:
    *       Get the worker instance 
    *           
    ************************************************************************/
    int GetInstance()
    {
        return _which;
    }
    
    /***********************************************************************/
    /** Purpose:
    *       Set the TaskQueue associated for this worker
    *       
    *  Input Parameters:
    *       its::TaskQueueTransport * queue - Task Queue Transport
    *   
    *  Notes:
    ************************************************************************/
    void SetTransport(its::TaskQueueTransport * queue)
    {
        _queue = queue;
    }
    
    /***********************************************************************/
    /** Purpose:
    *       Thread function for this worker
    *          
    *  Notes:
    *
    ************************************************************************/
    void Execute(void *arg)
    {
        its::Event event;

        while (!doExit)
        {
            if (isMsgRouter)
            {
               DIAThreadIdList::AddToThreadIdTable(_queue->GetInstance()); 
            }
            if (_queue->GetNextEvent(event) == ITS_SUCCESS)
            {
                MessageHandler *hd = GetMessageHandler(event.GetSource());
                if (hd)
                {
                    hd->HandleMessage(this, event);
                }
            }     
        }            
    }
    
    /***********************************************************************/
    /** Purpose:
    *       Set Exit for this worker
    *          
    *  Notes:
    *
    ************************************************************************/
    void SetExit()
    {
        doExit = ITS_TRUE;
    }
    /***********************************************************************/
    /** Purpose:
    *       Set Message Handler for this worker
    *          
    *  Notes:
    *
    ************************************************************************/      
    int RegisterMessageHandlers(std::vector <MessageHandler *>handlers)
    {
        _handlers = handlers;        
        return (ITS_SUCCESS);
    }     
    /***********************************************************************/
    /** Purpose:
    *       Get Message Handler for this worker
    *          
    *  Input Parameters:
    *       src - Message Handler associated with this src
    *
    ************************************************************************/    
    MessageHandler* GetMessageHandler(ITS_USHORT src)
    {
        for (unsigned int i = 0; i < _handlers.size(); i++)
        {
            if (_handlers[i]->GetMessageHandlerType() == src)
            {
                return _handlers[i];
            }
        }
        
        for (unsigned int i = 0; i < _handlers.size(); i++)
        {
            if (_handlers[i]->GetMessageHandlerType() == ITS_NO_SRC)
            {
                return _handlers[i];
            }
        }
        return NULL;
    }

private:
    bool isMsgRouter;
    int _which;
    its::TaskQueueTransport *_queue;
    ITS_BOOLEAN doExit;
    std::vector <MessageHandler *>_handlers;
};

/** DIAModule 
 *****************************************************************************
 *  Interface:
 *      DiaModule 
 *      
 *  Purpose:
 *      Provides an interface for application developers to
 *      design a multi-threaded application.Worker is a Thread with
 *      an associated TaskQueue Transport.Multiple threads can be configured
 *      to receive/wait-for events from a single-task-queue transport.
 *
 *****************************************************************************/
class DIAModule
{
public:
    /***********************************************************************/
    /** Purpose:
    *       DIA Module Base Class Constructor.
    *       
    *  Input Parameters:
    *       numThreads - Number of threads/workers for this module
    *       qName - The name of the task queue associated for these workers
    *       qId   - The queue Id or instance
    *       
    ************************************************************************/
    //Warning fix - deprecated conversion from string constant to char*
    DIAModule(int numThreads, const char *qName, ITS_USHORT qId, bool routerFlag = false)
    {
        _numThreads = numThreads;
        _qName = strdup(qName);
        _qId = qId;
        _handlers.reserve(10);
        _queue = NULL;
        qInitialized = false;
        isMsgRouter = routerFlag;

        //Initialing Uninitialized Pointer Value
        _queue = NULL;
        qInitialized = false;

        for (int iIndex = 0; iIndex < MAX_WORKERS_PER_MODULE; iIndex++)
        {
           workers[iIndex] = NULL;
        }

    }
    /***********************************************************************/
    /** Purpose:
    *       Destruct a dia module
    *           
    ************************************************************************/
    virtual ~DIAModule()
    { 
        if (_qName)
        {
            free (_qName);
        }
    }

    /***********************************************************************/
    /** Purpose:
    *       Get the TaskQueue associated for this Module
    *       
    *  Output Parameters:
    *       its::TaskQueueTransport * queue - Task Queue Transport
    *   
    *  Notes:
    ************************************************************************/
    its::TaskQueueTransport *GetTransport()
    {
        if (qInitialized)
        {
            return _queue;
        }
        else
        {
            return (NULL);
        }
    }

    /***********************************************************************/
    /** Purpose:
    *       Actually start a Module
    *       
    *  Notes:
    ************************************************************************/
    int Start()
    {
        InitTransport();
        
        if (_numThreads > MAX_WORKERS_PER_MODULE)
        {
            return ITS_EINITFAIL;
        }            
            
        for (int i=0; i < _numThreads; i++)
        {
            workers[i] = new DIAWorker(i, isMsgRouter);
            workers[i]->SetTransport(_queue);
            
            if (_handlers.size())
            {
                workers[i]->RegisterMessageHandlers(_handlers);
            }
            
            workers[i]->Start();
        }
        TRANSPORT_IS_ACTIVE(_queue->GetTC()) = ITS_TRUE; 
        return ITS_SUCCESS;
    }
    /***********************************************************************/
    /** Purpose:
    *       Stop a Module
    *       
    *  Notes:
    ************************************************************************/
    virtual int Stop()
    {
        for (int i=0; i < _numThreads; i++)
        {
            workers[i]->SetExit();
        }
        TRANSPORT_IS_ACTIVE(_queue->GetTC()) = ITS_FALSE; 
        return ITS_SUCCESS;
    }
    /***********************************************************************/
    /** Purpose:
    *      Register a MessageHandler for a particular src.
    *
    *  Input Parameters:
    *
    *       MessageHandler *handler: Pointer to a MessageHandler
    *
    *       ITS_USHORT src: The event src
    *
    *  Notes:
    *       None
    ************************************************************************/    
    int RegisterMessageHandler(MessageHandler *handler, ITS_USHORT src)
    {              
        _handlers.push_back(handler);        
        return (ITS_SUCCESS);
    }
    
protected:
    /***********************************************************************/
    /* Purpose:
    *       Set/Initialize the Task Queue Transport associated with this Module
    *       
    *  Notes:
    ************************************************************************/
    void InitTransport()
    {
       _queue = new its::TaskQueueTransport(_qName, _qId, ITS_TRANSPORT_TQUEUE);
       qInitialized = ITS_TRUE;
    }
    
private:
    char *_qName;
    bool isMsgRouter;
    ITS_USHORT _qId;
    int _numThreads;
    its::TaskQueueTransport *_queue;
    ITS_BOOLEAN qInitialized;
    DIAWorker *workers[MAX_WORKERS_PER_MODULE];
    std::vector <MessageHandler *>_handlers;

};

#endif
