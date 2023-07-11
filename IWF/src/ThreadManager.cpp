#include "ThreadManager.h"
#include <algorithm>

extern bool gisShutdownInProgress;
ThreadManager* ThreadManager::mSelfPtr = NULL;

ThreadManager::ThreadManager()
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    mNumThreads = engine::workerPool->GetThreadCount() - 1;
    if (mNumThreads > MAX_NO_THREADS)
    {
        DLOG_WARNING("No. of threads configured is more than max = %d, so %d threads are created",MAX_NO_THREADS,MAX_NO_THREADS);
        mNumThreads = MAX_NO_THREADS;
    }
    else if (mNumThreads < MIN_NO_THREADS)
    {
        DLOG_ERROR("No threads will be created, configure at least 2");
        mNumThreads = DEF_NO_THREADS;
    }
    else
    {
        // do nothing
    }

    mIndex = 0;
    DispatchOnThread();
    MUTEX_CreateMutex(&mMutex,0);
    for (int i = 0;i< MAX_NO_THREADS;i++)
    {
        mAppQueueCount[i] = 0;
    }
}

ThreadManager::~ThreadManager()
{
}

ThreadManager* ThreadManager::GetInstance()
{
    if (mSelfPtr == NULL)
    {
        mSelfPtr = new ThreadManager();
    }
    return mSelfPtr;
}

void ThreadManager::Destroy()
{
    delete mSelfPtr;
}

extern "C"
void AppThreadFunc(its::ThreadPoolThread* thr, void* arg)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    its::Event event;
    TransactionManager tm;
    int    ret = ITS_SUCCESS;
    ITS_Worker* worker = static_cast<ITS_Worker*> (thr);
    DiaMsg *dmsg = 0;
    while(!worker->GetExit())
    {
        try
        {
            int val = worker->GetNextEvent(event);
            if (ITS_SUCCESS != val)
            {
                DLOG_WARNING("Event not received from worker");
                continue;
            }

            /*
             * This method is used for decrementing queue count for thread
             * As this method uses the locking and unlocking mechanism of mutex
             * So commented this method call, this method needs for dbugging purpose
             */
            //ThreadManager::GetInstance()->DecreamentCount(worker->GetInstance());
 
            if (!gisShutdownInProgress)
            {
                switch (event.GetSource())
                {
                    case ITS_TCAP_CCITT_SRC:

                        DLOG_DEBUG("AppThreadFunc: CCITT SRC");
                        ret = tm.ProcessTcapMsg(event);
                        break;

                    case ITS_DIA_SRC:
                        {
                            DLOG_DEBUG("AppThreadFunc: DIAMETER SRC");
                            if (DiaFrame::GetDiaFrame()->Receive(event, &dmsg) != ITS_SUCCESS)
                            {
                                DLOG_WARNING("AppThreadFunc: Diameter message not received so returning from DIAMETER SRC");
                                return;
                            }

                            try
                            {
                                if (dmsg->GetMessageType() == ITS_DIA_MSG_TYPE_DATA)
                                {
                                    const DIA_BASE_CMD *dcmd = dmsg->GetMsgFlow();
                                    DIA_BASE_CMD *cmd = (DIA_BASE_CMD*) dcmd;
                                    ret = tm.ProcessDiaMsg(cmd);
                                    DLOG_DEBUG("AppThreadFunc: Return Value = %d", ret);
                                }
                                else if(dmsg->IsIndication())
                                {
                                    DLOG_DEBUG("AppThreadFunc: Diameter indication received");
                                    ret = tm.ProcessDiaTimeout(dmsg);
                                }
                                else if (dmsg->GetMessageType() == ITS_DIA_MSG_TYPE_IND_WITH_DATA)
                                {
                                    ITS_UINT index=0;
                                    DLOG_DEBUG("Message type indication with data");
                                    const ITS_OCTET *data = event.GetData();
                                    index++;

                                    // consume SessIdx and ApplId
                                    index += sizeof(ITS_UINT) + sizeof(ITS_UINT);

                                    // Get the Base Command. This is called before decoding.
                                    ITS_ULONG cmdAddr;
                                    memcpy(&cmdAddr, &data[index],sizeof(ITS_ULONG));
                                    DIA_BASE_CMD *gCmd = (DIA_BASE_CMD*)cmdAddr;
                                    ret = tm.ProcessDiaMsgIndicationWithData(gCmd);
                                }
                            }
                            catch (...)
                            {
                                DLOG_DEBUG("AppThreadFunc:: Caught An Unknown Exception:");
                                ret = ITS_SUCCESS;
                            }

                            if (dmsg)
                            {
                                delete dmsg;
                                dmsg = NULL;
                            }
                            break;
                        }
                    case ITS_TIMER_SRC :
                        {
                            DLOG_DEBUG("AppThreadFunc: TIMER SRC");
                            ByteArray octData;
                            STimerContext timerCtxtData;
                            ITS_TimerData *td;
                            td = (ITS_TimerData*)event.GetData();
                            memcpy(&timerCtxtData, td->context, sizeof(STimerContext));
                            tm.HandleTimeout(timerCtxtData);
                            break;
                        }
                        // Purge request from CLI, comes through the application only
                    case ITS_DEFAULT_USER_SRC :
                        {
                            DLOG_DEBUG("AppThreadFunc: ITS_DEFAULT_USER_SRC SRC");
                            // Check if the header is deadbeef
                            ITS_OCTET* eventRequestData = (ITS_OCTET*)event.GetData();
                            if (eventRequestData &&
                                    (eventRequestData[0] == 0xde &&
                                     eventRequestData[1] == 0xad &&
                                     eventRequestData[2] == 0xbe))
                            {
                                if(eventRequestData[3] == 0xef)
                                {
                                    std::string strIMSIToClear((char*)(eventRequestData + 4),
                                            event.GetLength() - 4);
                                    tm.HandlePurgeSubscriberRequest(
                                            strIMSIToClear);
                                }
                                else if(eventRequestData[3] == 0xed)
                                {
                                    tm.HandleDumpIwfInfoRequest();
                                }
                            }
                            break;
                        }


                    default:
                        DLOG_DEBUG("AppThreadFunc: UNKNOWN SRC");
                        break;
                }
            }
            else
            {
                DLOG_DEBUG("IWF process shutdown in progress, will not process any messages");
                if (event.GetSource() == ITS_TIMER_SRC)
                {
                    ByteArray octData;
                    STimerContext timerCtxtData;
                    ITS_TimerData *td;
                    td = (ITS_TimerData*)event.GetData();
                    memcpy(&timerCtxtData, td->context, sizeof(STimerContext));
                    if (timerCtxtData.m_eKeyType == EKeyType::BULK_FETCH)
                    {
                        DLOG_DEBUG("AppThreadFunc: Bulk fetch data received");
                        tm.HandleTimeout(timerCtxtData);
                    }
                }
            }
        }
        catch(std::exception& e)
        {
            DLOG_DEBUG("Uncaught exception!! %s", e.what());
        }
        catch(...)
        {
            DLOG_DEBUG("Uncaught... unknown exception!!!");
        }
    }
    DLOG_DEBUG("Exit AppThreadFunc");
}

void ThreadManager::DispatchOnThread()
{
    int ret;
    ITS_ThreadPoolEntry ent;
    /* 
     * Reap a thread from the Accelero Managed ThreadPool.
     */
    DLOG_DEBUG("ThreadCount = %d",mNumThreads);
    
    for (int i = 0; i < mNumThreads; i++)
    {
        if (engine::workerPool->GetFirstAvailThread (ent) == ITS_SUCCESS)
        {
            /*
             * Get the thread from the thread pool
             */
            engine::Worker * work;
            work = (engine::Worker *) ent.GetThread ();
            if (work)
            {
                /* 
                 * Dispatch the thread to simulate the base protocol application
                 */ 
               ret =
                    engine::workerPool->DispatchOnThread (ent,
                            (ITS_ThreadCallFunc)
                            AppThreadFunc, NULL);

                /*
                 * If the dispatch fails, return the thread to the thread pool
                 * and throw the error.
                 */
                if (ret != ITS_SUCCESS)
                {
                    engine::workerPool->ReturnToAvailThreads (ent);

                    ITS_THROW_ERROR (ret);
                }
 
                // Save the current transport instance in available queue
                mAvailThreadsList[mIndex++] = work->GetInstance();
            }
            else
            {
                engine::workerPool->ReturnToAvailThreads (ent);
            }
        }
    }
}

void ThreadManager::PutEvent(its::Event& event)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    /*
     * This method is used for incrementing queue count for thread
     * As this code uses the locking and unlocking mechanism of mutex
     * So commented these lines of code, this code  needs for dbugging purpose
     */
    /*pthread_mutex_lock(&mMutex);
    mAppQueueCount[GetIndex(mCurrThreadId)]++;
    DLOG_DEBUG("After increment threadID=%d : Queue Count : %d",mCurrThreadId,mAppQueueCount[GetIndex(mCurrThreadId)]);
    pthread_mutex_unlock(&mMutex);*/
    its::Transport::PutEvent(mCurrThreadId,event);
}

void ThreadManager::DecreamentCount(int id)
{
    pthread_mutex_lock(&mMutex);
    mAppQueueCount[GetIndex(id)]--;
    pthread_mutex_unlock(&mMutex);
}

int ThreadManager::GetIndex(int threadID)
{
    int ret = -1;
    for (int i =0; i< MAX_NO_THREADS; i++)
    {
        if (mAvailThreadsList[i] == threadID)
        {
            ret = i;
            break;
        }
    }
    return ret;
}

void ThreadManager::MapEventToThread(its::Event& event)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("Got Event");
    if (event.GetSource() == ITS_TCAP_CCITT_SRC)
    {
        ITS_CTXT tcapDlgId = ITS_GET_CTXT(&event.GetData()[1]);
        DLOG_DEBUG("MapEventToThread : dlgID = %u\n",tcapDlgId);
        if (mDlgThMap.find(tcapDlgId) != mDlgThMap.end())
        {
            DLOG_DEBUG("Event already present");
        }
        else
        {
              if (mIndex == mNumThreads)
              {
                  mIndex = 0;
              }
              DLOG_DEBUG("Next available thread index mIndex = %d",mIndex);
              mDlgThMap[tcapDlgId] = mAvailThreadsList[mIndex];
              mIndex++;
        }
        mCurrThreadId = mDlgThMap[tcapDlgId];
       DLOG_DEBUG("ThreadID =  %d DialogID = %d",mCurrThreadId, tcapDlgId);
    }
    else if(event.GetSource() == ITS_DIA_SRC)
    {
        std::string diaSessionId;
        DiaMsg *dmsg = 0;
        if (DiaFrame::GetDiaFrame()->Receive(event, &dmsg) != ITS_SUCCESS)
        {
            DLOG_ERROR("Diameter message not received");
            return;
        }
        if (dmsg->GetMessageType() == ITS_DIA_MSG_TYPE_DATA) 
        {
            const DIA_BASE_CMD *dcmd = dmsg->GetMsgFlow();
            DIA_BASE_CMD *cmd = (DIA_BASE_CMD*) dcmd;
           diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(cmd))->GetBaseGenCommand();
           if ( diaBaseGenCmd->countSessionId() > 0 )
           {
               diaSessionId = diaBaseGenCmd->getSessionId()->value();
               DLOG_DEBUG("MapEventToThread SessionId = %s",diaSessionId.c_str());
           }
        }
        if (mSessionDlgMap.find(diaSessionId) != mSessionDlgMap.end())
        {
            DLOG_DEBUG("MapEventToThread SessionID = %s : dialogID = %d",diaSessionId.c_str(),mSessionDlgMap[diaSessionId]);
            mCurrThreadId = mDlgThMap[mSessionDlgMap[diaSessionId]];
        }
        DLOG_DEBUG(" %d %s %d",mCurrThreadId,diaSessionId.c_str(),mSessionDlgMap[diaSessionId]);
    }
    PutEvent(event);
}

void ThreadManager::SetSessionId(string sessionId, ITS_CTXT dlgId)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("SetSessionId sessionID =  %s : dialogID = %d",sessionId.c_str(),dlgId);
    pthread_mutex_lock(&mMutex);
    mSessionDlgMap[sessionId] = dlgId;
    pthread_mutex_unlock(&mMutex);
}

int ThreadManager::GetThreadQueueCount(int index)
{
    int ret = -1;
    pthread_mutex_lock(&mMutex);
    ret = mAppQueueCount[index];
    pthread_mutex_unlock(&mMutex);
    return ret;
}
