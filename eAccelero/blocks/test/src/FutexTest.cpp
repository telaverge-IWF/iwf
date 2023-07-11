#include "Sync.h"
#include "Thread.h"
#include <iostream>

//#define Futex Mutex
//#define ScopedFutex ScopedMutex

using namespace eAccelero;

class FutexTest: public Runnable
{
 public:
    FutexTest()
     : m_counter(0)
    {
    }
    ~FutexTest()
    {
    }
    void Run(void *arg)
    {
        //try
        {
            bool run = true;
            m_printFutex.lock();
            std::cout << "Running thread " << (long)arg << std::endl;
            m_printFutex.unlock();

            while(run)
            {
                run = TestFunc();
                ThisThread::Sleep(1);
            }
            m_printFutex.lock();
            std::cout << "Exiting thread " << (long)arg << std::endl;
            m_printFutex.unlock();
        }
#if 0
        catch(std::exception& exp)
        {
            std::cout << "Exception thrown on thread " << ThisThread::Name() <<
                " " << exp.what() << std::endl;
        }
        if (m_futex.tryLock())
        {
            std::cout << "Mutex locked " << (long)arg << std::endl;
        }
        else
        {
            std::cout << "Mutex unlocked " << (long)arg << std::endl;
        }
#endif
    }

    bool TestFunc()
    {
        Futex::ScopedFutex guard(m_futex);
        
        if (m_counter >= 0x1FFFFFFF)
        {
            return false;
        }
        for (int i = 0; i < 50000; i++)
        {
            m_counter++;
        }
        return true;
    }

 protected:
    unsigned m_counter;
    Futex m_futex;
    Futex m_printFutex;
};


int main()
{
    FutexTest f1;
    {
        Thread t1("one"), t2("two"), t3("three"), t4("four");

        t1.Start(&f1, (void*)1);
        t2.Start(&f1, (void*)2);
        t3.Start(&f1, (void*)3);
        t4.Start(&f1, (void*)4);
    }

    return 0;
}

