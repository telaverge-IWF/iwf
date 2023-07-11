#ifndef __EACC_Thread_h__
#define __EACC_Thread_h__

#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/unistd.h>
#include "Exception.h"
#include "Signal.h"
#include "ThreadSpec.h"

#include <utmpx.h>
#include <sched.h>

namespace eAccelero
{

EACC_DEFINE_EXCEPTION_CLASS(ThreadException, Exception, "Thread Exception")
#define ThreadExceptionLog(...) GEN_EXCEPTION_LOG(eAccelero::SocketException, ##__VA_ARGS__)

struct ThreadAttributes
{
	ThreadAttributes()
	  : detachState(PTHREAD_CREATE_JOINABLE),
	    schedPolicy(SCHED_OTHER),
		schedPriority(0),
		inheritSched(PTHREAD_EXPLICIT_SCHED),
		scope(PTHREAD_SCOPE_SYSTEM)
	{
	}
	
	int detachState; // PTHREAD_CREATE_JOINABLE, PTHREAD_CREATE_DETACHED
	int schedPolicy; // SCHED_OTHER, SCHED_RR, SCHED_FIFO
	int schedPriority; // 0 is the default
	int inheritSched; // PTHREAD_EXPLICIT_SCHED, PTHREAD_INHERIT_SCHED
	int scope; // PTHREAD_SCOPE_SYSTEM, PTHREAD_SCOPE_PROCESS
};

class Runnable
{
 public:
    virtual ~Runnable()
    {
    }
    virtual void Run(void *arg = NULL) = 0;
    /*
        This should be overrided in the new derived class inorder to 
        assign the new index for the statsindex (use below code)

            #include "Statistics.h" //include this header file
            eAccelero::StatsIndex = stats.getNewThreadIndex(); //put this code in the UpdateStatsIndex

        Make sure that you call this function only once. if you are updating statistics
    */
    virtual void UpdateStatsIndex();
};

class Thread
{
 public:
 	Thread(const char *name)
        : m_isOwner(true),
          m_threadId(0),
          m_attr(NULL),
          m_name(name)
    {
    }

	Thread(const char *name, const ThreadAttributes& thAttributes)
        : m_isOwner(true),
          m_threadId(0),
          m_attr(NULL),
          m_name(name)
    {
        this->SetAttributes(thAttributes);
    }

    Thread(const Thread& rhs)
        : m_isOwner(true),
          m_threadId(rhs.m_threadId),
          m_attr(rhs.m_attr),
          m_name(rhs.m_name)
    {
        rhs.m_isOwner = false;
    }

    Thread& operator=(const Thread& rhs)
    {
        if (this != &rhs)
        {
            rhs.m_isOwner = false;
            m_isOwner = true;
            m_threadId = rhs.m_threadId;
            m_attr = rhs.m_attr;
            m_name = rhs.m_name;
        }
        return *this;
    }
	
	~Thread()
    {
        if (m_isOwner)
        {
            this->Join();
            if (m_attr)
            {
                pthread_attr_destroy(m_attr);
                delete m_attr;
            }
        }
    }

    void Start(Runnable *obj, void *arg = NULL);

    template <typename C, typename A>
    void Start(C *obj, void (C::*cbk)(A*), A *arg = NULL);

	void SetAttributes(const ThreadAttributes& thAttributes);

	// A thread created in the joinable state can later be put in the detached
	// state
    void Detach()
    {
        int ret = pthread_detach(m_threadId);
        if (ret != 0)
        {
            throw ThreadException("Thread Detach Failed", ret);
        }
    }
    
    void* Join()
    {
        void* retVal = NULL;
        int ret = pthread_join(m_threadId, &retVal);
        if (ret != 0 && ret != EINVAL)
        {
            throw ThreadException("Join failed", ret);
        }
        return retVal;
    }
    // Non protable extensions like TryJoin and TimedJoin

	void Cancel()
    {
        int ret = pthread_cancel(m_threadId);
        if (ret != 0)
        {
            throw ThreadException("Join failed", ret);
        }
    }

    void Signal(int sigNum)
    {
        int ret = pthread_kill(m_threadId, sigNum);
        if (ret != 0)
        {
            throw ThreadException("Thread signal failed", ret);
        }
    }

    bool operator == (const Thread& rhs)
    {
        return pthread_equal(m_threadId, rhs.m_threadId);
    }
    bool operator != (const Thread& rhs)
    {
        return !pthread_equal(m_threadId, rhs.m_threadId);
    }


// TODO add pthread_cleanup_push, thread specific storage(key_create)

	pthread_t Id() const
	{
		return m_threadId;
	}

    const std::string& Name() const
    {
        return m_name;
    }

	void GetSchedParam(int& priority, int& policy)
    {
        struct sched_param schedParam;
        int ret = pthread_getschedparam(m_threadId, &policy, &schedParam);
        if (ret != 0)
        {
            throw ThreadException("Get Thread Sched parma failed", ret);
        }
        priority = schedParam.sched_priority;
    }

	void SetSchedParam(const int &priority, const int &policy)
    {
        struct sched_param schedParam;
        schedParam.sched_priority = priority;
        int ret = pthread_setschedparam(m_threadId, policy, &schedParam);
        if (ret != 0)
        {
            throw ThreadException("Get Thread Sched parma failed", ret);
        }
    }

    // returns the number of cpus
    static int NumCPUs()
    {
        return sysconf(_SC_NPROCESSORS_ONLN);
    }

 protected:

    static void* ThreadFunc(void *arg);

    static void* MemberThreadFunc(void *arg);
    
    mutable bool    m_isOwner;
 	pthread_t       m_threadId;
	pthread_attr_t* m_attr;
    std::string     m_name;
};

class InvokerBase
{
 public:    
    virtual ~InvokerBase() {}
    virtual void Invoke() = 0;
};

// TODO make this the standard whereever we are calling member function
// callbacks
// No args with return type as void
template <typename C, typename R=void>
class Invoker: public InvokerBase
{
 public:
    typedef R (C::*Callback)();

    Invoker(C *obj, Callback cbk)
        : m_obj(obj),
          m_cbk(cbk)
    {
    }
    virtual void Invoke()
    {
        if (m_obj && m_cbk)
        {
            (m_obj->*m_cbk)();
        }
    }
 protected:
    C *m_obj;
    Callback m_cbk;
};

class ThisThreadData
{
 public:
    static const unsigned InvalidId = 0xFFFFFFFF;
    ThisThreadData()
        : m_id(InvalidId),
          m_tid(0),
          m_onceData(NULL)
    {
    }
    ThisThreadData(const std::string &name, unsigned id)
        : m_name(name),
          m_id(id),
          m_onceData(NULL)
    {
    }
 
    std::string m_name;
    unsigned    m_id;
    pid_t       m_tid;    // Value of gettid

    InvokerBase* m_onceData;
};

class ThreadOnce;

// Functions to be invoked from calling thread context are encapsulated here
class ThisThread
{
 public:
    static pthread_t Self()
    {
        return pthread_self();
    }

    static bool Equals(pthread_t thr)
    {
        return pthread_equal(ThisThread::Self(), thr);
    }

    static bool Equals(Thread& thr)
    {
        return pthread_equal(ThisThread::Self(), thr.Id());
    }

    static void Detach()
    {
        int ret = pthread_detach(ThisThread::Self());
        if (ret != 0)
        {
            throw ThreadException("Thread detach failed", ret);
        }
    }
    
    static void Yield()
    {
        int ret = pthread_yield();
        if (ret != 0)
        {
            throw ThreadException("Yield failed", ret);
        }
    }

 	// This will terminate the current thread. The current thread
	// need not be the current object. To ensure that the current
	// thread is current object always execute this in the doWork
	// function(including inner functions).
    // This function doesn't return, the thread terminates here
    static void Exit(void *retVal = NULL)
    {
        pthread_exit(retVal);
    }

	// Enables/disables Cancellation
	// State can be PTHREAD_CANCEL_ENABLE or PTHREAD_CANCEL_DISABLE
	// Returns the previous Cancellation state
	static int SetCancelState(int state)
    {
        int oldState = 0;
        int ret = pthread_setcancelstate(state, &oldState);
        if (ret != 0)
        {
            throw ThreadException("Set Cancel State failed", ret);
        }
        return oldState;
    }

    static void NoCancel()
    {
        SetCancelState(PTHREAD_CANCEL_DISABLE);
    }

    // Can be PTHREAD_CANCEL_DEFERRED or PTHREAD_CANCEL_ASYNCHRONOUS
	// Returns the previous cancellation type
	static int SetCancelType(int type)
    {
        int oldType = 0;
        int ret = pthread_setcanceltype(type, &oldType);
        if (ret != 0)
        {
            throw ThreadException("Set Cancel type failed", ret);
        }
        return oldType;
    }

    // creates a cancellation  point  within  the
    // calling  thread, so that a thread that is otherwise executing code that
    // contains no cancellation points will respond to a cancellation request.
    static void CancelPoint()
    {
        pthread_testcancel();
    }

    static void Sleep(int ms)
    {
        int ret;
        struct timespec ts;
        struct timespec remTime = {0, 0};

        ts.tv_sec = (ms / 1000);
        ts.tv_nsec = (ms % 1000) * 1000 * 1000;

        while ((ret = nanosleep(&ts, &remTime)) < 0 
                && errno == EINTR)
        {
            ts = remTime;
        }         
    }

    // TODO make this a thread specific store, instead of making a syscall 
    // everytime a trace is generated
    // Not portable to non GNU
    static pid_t GetThreadId()
    {
        pid_t& tid = static_cast<ThisThreadData*>(m_data)->m_tid;
        if (tid == 0)
        {
            tid = syscall(SYS_gettid);
        }
        return tid;
    }

    // CPU number starts with 0 and can have max cpus
    static void SetCPU(int cpuNum)
    {
        cpu_set_t cpuSet;

        CPU_ZERO(&cpuSet);
        CPU_SET(cpuNum, &cpuSet);

        int ret = sched_setaffinity(0, sizeof(cpuSet), &cpuSet);
        if (ret != 0)
        {
            throw ThreadException("Set affinity failed");
        }        
    }

    // Get the CPU on whcih the current thread is running
    static int GetCPU()
    {
        return sched_getcpu();
    }

    static void SigBlockAll()
    {
        SigSet set;
        set.Fill();
        SigSet::SetMask(SIG_BLOCK, &set);
    }

    static void SigUnblockAll()
    {
        SigSet set;
        set.Fill();
        SigSet::SetMask(SIG_UNBLOCK, &set);
    }

    static void SetMask(int how, SigSet *set = NULL, SigSet *old = NULL)
    {
        SigSet::SetMask(how, set, old);
    }

    static void SetName(std::string name)
    {
        m_data->m_name = name;
    }
    static const char* Name()
    {
        return m_data->m_name.c_str();
    }

    // Main thread does not invoke the Destructor, do it at exit
    static void MainCleanup()
    {
        ThisThreadData *data = m_data.GetData();
        if (data)
        {
            delete data;
        }
    }

    friend class Thread;
    friend class ThreadOnce;
protected:
    // Thread specific storage
    static ThreadSpec<ThisThreadData> m_data;

    // Thread Data stored in the stack.
    //   Current logger etc... can go into this
}; // class ThisThread

class ThreadOnce
{
 public:
    ThreadOnce()
        : m_onceCtl(PTHREAD_ONCE_INIT)
    {
    }

    // Will execute the method only once
    template <typename T>
    void RunOnce(T *obj, void (T::*onceRoutine)())
    {
        Invoker<T> ivk(obj, onceRoutine);
        ThisThread::m_data->m_onceData = &ivk;
        pthread_once(&m_onceCtl, ThreadOnce::OnceRoutine);
        ThisThread::m_data->m_onceData = NULL;
    }
 protected:
    static void OnceRoutine()
    {
        if (ThisThread::m_data->m_onceData)
        {
            ThisThread::m_data->m_onceData->Invoke();
        }
    }

    pthread_once_t m_onceCtl;
};

struct MemberCbkDataBase
{
    MemberCbkDataBase(const std::string& n, unsigned i)
        : name(n),
          id(i)
    {
    }
    virtual ~MemberCbkDataBase() {}
    virtual void Invoke() = 0;

    std::string name;
    unsigned    id;
};

template <typename C, typename A>
struct MemberCbkData: public MemberCbkDataBase
{
    typedef void (C::*Callback)(A*);

    MemberCbkData(C *o, Callback c, const std::string& n, 
                  unsigned id, A *a = NULL)
      : MemberCbkDataBase(n, id),
        obj(o),
        cbk(c),
        arg(a)
    {
    }
    ~MemberCbkData()
    {
    }

    void Invoke()
    {
        if (obj && cbk)
        {
            (obj->*cbk)(arg);
        }
    }

    C *obj;
    Callback cbk;
    A *arg;
};

template <typename C, typename A>
void Thread::Start(C *obj, void (C::*cbk)(A*), A *arg)
{
    SigSet sig, oldSig;
    sig.Fill();
    sig.SetMask(SIG_BLOCK, &sig, &oldSig);
    
    MemberCbkData<C, A> *data = new MemberCbkData<C, A>(obj, cbk, m_name, 0, arg);
    int ret = pthread_create(&m_threadId, m_attr, &Thread::MemberThreadFunc, data);
    if (ret != 0)
    {
        throw ThreadException("Thread Creation Failed", ret);
    }

    // Reset the old signal mask after starting the thread
    sig.SetMask(SIG_SETMASK, &oldSig);
}

} // namespace eAccelero

#endif
