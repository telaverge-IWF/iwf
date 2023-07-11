#include "ThreadQueue.h"
#include "Thread.h"

using namespace eAccelero;

ThreadQueue<int> g_tqueue;

struct Data
{
    std::string name;
    int val;
};

ThreadSharedData<Data*> g_shared;

struct Producer: public Runnable
{
    void Run(void *arg)
    {
        for (int i = 0; i < 50; i++)
        {
            g_tqueue.Push(i);
            ThisThread::Sleep(10);
        }


        // Wait for shared data
        Data *data = NULL;
        g_shared.Get(data);
        std::cout << "Got shared data from " << data->name 
                  << " Val: " << data->val << std::endl;
        delete data;

        std::cout << ThisThread::Name() << " exiting...\n";
    }
};

struct Consumer: public Runnable
{
    void Run(void *arg)
    {
        int val = 0;
        while (val != 49)
        {
            g_tqueue.WaitAndPop(val);
            std::cout << ThisThread::Name() << ": " << val << std::endl;
        }

        // Sharing data with other thread
        ThisThread::Sleep(1000);
        std::cout << "Sending shared data...\n";
        Data *data = new Data();
        data->name = ThisThread::Name();
        data->val  = 42;
        g_shared.Set(data);


        std::cout << ThisThread::Name() << " exiting...\n";
    }
};

int main()
{
    Producer p;
    Consumer c;
    Thread prod("Producer");
    Thread cons("Consumer");

    cons.Start(&c);
    prod.Start(&p);

    return 0;
}

