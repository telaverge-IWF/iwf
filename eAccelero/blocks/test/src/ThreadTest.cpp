#include "Thread.h"

#include <sys/signalfd.h>

#define THR_SIGNAL (SIGRTMIN + 1)

using namespace eAccelero;

class TestThread: public Runnable
{
 public:
    TestThread()
    {
    }
    ~TestThread()
    {
    }
    void Run(void *arg);
    void RunOnce();

    void AnotherThread(int* arg)
    {
        std::cout << "This is member function cbk thread: " << *arg << std::endl;
        ThisThread::Sleep(1000);
        std::cout << "Exiting Member function thread. " << ThisThread::Name() << std::endl;

        delete arg;
    }
protected:
    static ThreadOnce m_onceCtl;
};

ThreadOnce TestThread::m_onceCtl;

class ThreadManager
{
 public:
    ThreadManager(int numThreads)
        : m_threads(NULL),
          m_runnables(NULL),
          m_numThreads(0)
    {
        m_threads = new Thread*[numThreads];
        m_runnables = new Runnable*[numThreads];
        for (int i = 0; i < numThreads; i++)
        {
            m_threads[i] = NULL;
            m_runnables[i] = NULL;
        }
        m_numThreads = numThreads;
        m_self = this;
    }
    ~ThreadManager()
    {
        for (int i = 0; i < m_numThreads; i++)
        {
            if (m_threads[i])
            {
                delete m_runnables[i];
                delete m_threads[i];
            }
        }
        delete []m_runnables;
        delete []m_threads;
    }

    void StartThread(int threadNum, Runnable *obj)
    {
        if (threadNum >= m_numThreads)
        {
            throw std::out_of_range("Start thread failed, out of range");
        }
        char name[64];
        sprintf(name, "Thread %d", threadNum);
        m_threads[threadNum] = new Thread(name);
        m_runnables[threadNum] = obj; 
        m_threads[threadNum]->Start(obj, (void*)threadNum);
    }

    void StartMAThread(int threadNum, TestThread *obj, int *arg)
    {
        if (threadNum >= m_numThreads)
        {
            throw std::out_of_range("Start thread failed, out of range");
        }
        char name[64];
        sprintf(name, "Thread %d", threadNum);
        m_threads[threadNum] = new Thread(name);
        m_runnables[threadNum] = obj; 
        m_threads[threadNum]->Start(obj, &TestThread::AnotherThread, arg);
    }

    Thread& GetThread(int threadNum)
    {
        if (threadNum >= m_numThreads)
        {
            throw std::out_of_range("Get thread failed, out of range");
        }
        return *m_threads[threadNum];
    }

    static ThreadManager& GetMe()
    {
        return *m_self;
    }

 protected:
    Thread   **m_threads;
    Runnable **m_runnables;
    int m_numThreads;

    static ThreadManager *m_self;
};

void TestThread::Run(void *arg)
{
    long tNum = (long)(arg);

    m_onceCtl.RunOnce(this, &TestThread::RunOnce);

    std::cout << "Entering Thread: " << ThisThread::Name() << std::endl;
    if (tNum == 0)
    {
        SigSet set;
        set.Add(THR_SIGNAL);
        int sigFD = signalfd(-1, set, 0);
        if (sigFD < 0)
        {
            throw ThreadException("Signal FD failed");
        }

        struct signalfd_siginfo si;
        memset(&si, 0, sizeof(si));
        int ret = read(sigFD, &si, sizeof(si));
        if (ret < 0)
        {
            throw ThreadException("Read signal FD failed");
        }

        std::cout << "Signal " << si.ssi_signo 
            << " caught by Thread " << tNum << std::endl;
    }
    else if (tNum == 1)
    {
        std::cout << "Signalling the Thread 0 from " << ThisThread::Name() << std::endl;
        ThreadManager::GetMe().GetThread(0).Signal(THR_SIGNAL);
    }
}

void TestThread::RunOnce()
{
    std::cout << "Runonce called from " << ThisThread::Name() << std::endl;
}


ThreadManager * ThreadManager::m_self = NULL;


int main()
{
    ThreadManager tm(3);

    //ThisThread::SetName("Main");

    tm.StartThread(0, new TestThread());
    ThisThread::Sleep(1);
    tm.StartThread(1, new TestThread());
    ThisThread::Sleep(1);

    TestThread *at = new TestThread();
    int *num = new int;
    *num = 42;
    tm.StartMAThread(2, at, num);

    //std::cout << "Exiting " << ThisThread::Name() << std::endl;

    // Main thread, thread specific store, will not be deleted automatically
    // Call the cleanup function
    ThisThread::MainCleanup();

    return 0;
}

