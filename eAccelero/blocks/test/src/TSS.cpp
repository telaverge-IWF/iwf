
#include <thread>
#include <time.h>
#include "ThreadSpec.h"
#include "Atomic.h"

using namespace eAccelero;

class ThreadData
{
 public:
    ThreadData()
    {
    }
    int m_data;
};

Atomic<> g_counter;

class TestThreadPool
{
 public:
    TestThreadPool()
    {
    }

    // thread run function
    void operator ()()
    {
        ThreadData* d = s_tss;
        d->m_data = g_counter++;
        std::cout << "In thread " << d->m_data << std::endl;

        sleep(2);

        PrintFunc();
    }
    void PrintFunc()
    {
        ThreadData *d = s_tss;
        std::cout << "Exiting thread " << d->m_data << std::endl;
    }
 protected:
    static ThreadSpec<ThreadData> s_tss;
};

ThreadSpec<ThreadData> TestThreadPool::s_tss;

int main()
{
    TestThreadPool tp;
    std::thread tc1(tp);
    sleep(1);
    std::thread tc2(tp);
    sleep(1);
    std::thread tc3(tp);

    tc1.join();
    tc2.join();
    tc3.join();

    return 0;
}

