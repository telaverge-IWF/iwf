#include "Thread.h"
#include "Statistics.h"

using namespace eAccelero;


struct ThreadCbkData
{
    ThreadCbkData(Runnable *o, const std::string& n, unsigned i, void *a = NULL)
        : obj(o),
          arg(a),
          name(n),
          id(i)
    {
    }

    Runnable* obj;
    void*     arg;
    std::string name;
    unsigned    id;
};

ThreadSpec<ThisThreadData> ThisThread::m_data;


void Runnable::UpdateStatsIndex()
{
     StatsIndex = statistics.getNewThreadIndex();
}


void Thread::Start(Runnable *obj, void *arg)
{
    // Start the thread with all signals blocked, to avoid race conditions
    SigSet sig, oldSig;
    sig.Fill();
    sig.SetMask(SIG_BLOCK, &sig, &oldSig);
     
    ThreadCbkData *data = new ThreadCbkData(obj, m_name, 0, arg);
    int ret = pthread_create(&m_threadId, m_attr, &Thread::ThreadFunc, data);
    if (ret != 0)
    {
        throw ThreadException("Thread Creation Failed", ret);
    }

    // Reset the old signal mask after starting the thread
    sig.SetMask(SIG_SETMASK, &oldSig);
}

void* Thread::ThreadFunc(void *data)
{
    ThreadCbkData *cbkData = reinterpret_cast<ThreadCbkData *>(data);

    // By default all the signals are blocked.

    // Make thread non cancellable. This makes handling stuff easier
    ThisThread::NoCancel();

    // Initialize any thread specfic stack data here
    ThisThread::m_data = new ThisThreadData(cbkData->name, cbkData->id);

    cbkData->obj->Run(cbkData->arg);

    delete cbkData;

    return NULL;
}

void* Thread::MemberThreadFunc(void *data)
{
    MemberCbkDataBase *cbkData = reinterpret_cast<MemberCbkDataBase *>(data);

    // Make thread non cancellable. This makes handling stuff easier
    ThisThread::NoCancel();

    // Initialize any thread specfic stack data here
    ThisThread::m_data = new ThisThreadData(cbkData->name, cbkData->id);

    cbkData->Invoke();

    delete cbkData;

    return NULL;
}

