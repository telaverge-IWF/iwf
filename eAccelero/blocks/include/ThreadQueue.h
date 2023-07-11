#ifndef __ThreadQueue_h__
#define __ThreadQueue_h__

#include "Sync.h"
#include <queue>

namespace eAccelero
{

template <typename T>
class ThreadQueue
{
 public:
    ThreadQueue()
    {
    }
    ~ThreadQueue()
    {
    }
    
    void Push(T &data)
    {
        ScopedLock<Mutex> guard(m_cond.mutex());
        m_queue.push(data);
        m_cond.signal();
    }

    // Blocks till a message is received
    // Thread must not be in a cancellable state
    void WaitAndPop(T& data)
    {
        ScopedLock<Mutex> guard(m_cond.mutex());
        while(m_queue.empty())
        {
            m_cond.wait();
        }

        data = m_queue.front();
        m_queue.pop();
    }

    // On timeout return false
    bool WaitAndPop(T& data, int uSec)
    {
        ScopedLock<Mutex> guard(m_cond.mutex());
        while (m_queue.empty())
        {
            if (m_cond.wait(uSec) != 0)
            {
                // Timeout
                return false;
            }
        }

        data = m_queue.front();
        m_queue.pop();

        return true;
    }

    // Get the first entry if present. Or return false
    bool Peek(T &data)
    {
        ScopedLock<Mutex> guard(m_cond.mutex());
        if (m_queue.empty())
        {
            return false;
        }
        data = m_queue.front();
        return true;
    }
    // Remove the first entry if present. Or return false
    bool TryPop(T& data)
    {
        ScopedLock<Mutex> guard(m_cond.mutex());
        if (m_queue.empty())
        {
            return false;
        }
        data = m_queue.front();
        m_queue.pop();
        return true;
    }

    int Size()
    {
        ScopedLock<Mutex> guard(m_cond.mutex());
        return m_queue.size();
    }

    bool Empty()
    {
        ScopedLock<Mutex> guard(m_cond.mutex());
        return m_queue.empty();
    }

 protected:
    std::queue<T> m_queue;
    CondVar       m_cond;
};

// This is like a queue with single entry
template <typename T>
class ThreadSharedData
{
 public:
    ThreadSharedData()
        : m_data(),
          m_isDataSet(false)
    {
    }
    ~ThreadSharedData()
    {
    }
    // Waits 
    void Get(T& data)
    {
        ScopedLock<Mutex> guard(m_cond.mutex());
        while(!m_isDataSet)
        {
            m_cond.wait();
        }
        data = m_data;
        m_isDataSet = false;
    }
    // Returns false on timeout
    bool Get(T& data, int uSec)
    {
        ScopedLock<Mutex> guard(m_cond.mutex());
        while (!m_isDataSet)
        {
            if (m_cond.wait(uSec) != 0)
            {
                // Timeout
                return false;
            }
        }        
        data = m_data;
        m_isDataSet = false;
        return true;
    }
    void Set(T& data)
    {
        ScopedLock<Mutex> guard(m_cond.mutex());
        m_data = data;
        m_isDataSet = true;
        m_cond.signal();
    }

 protected:
    CondVar m_cond;
    T       m_data;
    bool    m_isDataSet;
};

} // namespace eAccelero

#endif // __ThreadQueue_h__
