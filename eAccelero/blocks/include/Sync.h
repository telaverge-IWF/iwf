#ifndef __EACC_Sync_h__
#define __EACC_Sync_h__

#include "Exception.h"
#include "TimeVal.h"

#include <unistd.h>
#include <sys/syscall.h>
#include <linux/futex.h>
#include "Atomic.h"

namespace eAccelero
{

EACC_DEFINE_EXCEPTION_CLASS(SyncException, Exception, "Sync Exception")
#define SyncExceptionLog(...) GEN_EXCEPTION_LOG(SystemException, ##__VA_ARGS__)

template <typename M>
class ScopedLock
{
 public:
    ScopedLock(M& m)
        : m_mutex(&m)
    {
        m_mutex->lock();
    }
    ScopedLock(M& m, int uSec)
    {
        m_mutex->lock(uSec);
    }
    inline void unlock()
    {
        m_mutex->unlock();
        m_mutex = NULL;
    }
    ~ScopedLock()
    {
        if (m_mutex)
        {
            m_mutex->unlock();
        }
    }
 private:
    M* m_mutex;
};

class MutexAttributes
{
 public:
    // Priority Ceiling and protocol not supported
    // type can be PTHREAD_MUTEX_NORMAL, PTHREAD_MUTEX_ERRORCHECK,
    //             PTHREAD_MUTEX_RECURSIVE, PTHREAD_MUTEX_DEFAULT
    // processShared can be PTHREAD_PROCESS_PRIVATE or PTHREAD_PROCESS_SHARED
    MutexAttributes(int type = PTHREAD_MUTEX_DEFAULT,
                    int processShared = PTHREAD_PROCESS_PRIVATE);

    ~MutexAttributes();

    operator pthread_mutexattr_t*();

 private:
    pthread_mutexattr_t m_attr;
};


class Mutex
{
  public:
    // preferred way of implementing a mutex
    typedef ScopedLock<Mutex> ScopedMutex;

    // Non-recursive mutex (NORMAL) are faster
    Mutex(int type = PTHREAD_MUTEX_NORMAL);

    Mutex(MutexAttributes& attr);

    ~Mutex();

    void lock();

    int lock(int uSec);

    void unlock();

    int tryLock();

    operator pthread_mutex_t*();

  private:
    pthread_mutex_t m_lock;
};


class CondVarAttributes
{
 public:
    // processShared values are PTHREAD_PROCESS_PRIVATE or PTHREAD_PROCESS_SHARED
    CondVarAttributes(int processShared = PTHREAD_PROCESS_PRIVATE);

    ~CondVarAttributes();

    operator pthread_condattr_t*();

 private:
    pthread_condattr_t m_condAttr;
};


class CondVar
{
  public:
    CondVar();

    CondVar(MutexAttributes& lAttr, CondVarAttributes& cvAttr);

    ~CondVar();

    void lock();

    void unlock();

    void wait();

    int wait(int uSec);

    void signal();

    void broadcast();

    Mutex& mutex();

  private:
    Mutex m_lock;
    pthread_cond_t m_cond;
};

// inline functions
inline MutexAttributes::operator pthread_mutexattr_t*()
{
    return &m_attr;
}

inline void Mutex::lock()
{
    int ret;
    ret = pthread_mutex_lock(&m_lock);
    if (0 != ret)
    {
        std::cerr <<"Mutex init failed with return value"<<ret<<std::endl;
        throw SyncException("Mutex init failed", ret);
    }
}

inline int Mutex::lock(int uSec)
{
    int ret = 0;
    struct timespec absTime;
    TimeVal tv;
    tv.now().addUSec(uSec);
    tv.toTimeSpec(absTime);

    ret = pthread_mutex_timedlock(&m_lock, &absTime);
    if (0 != ret)
    {
        if (ETIMEDOUT == ret)
        {
            return ret;
        }
        throw SyncException("Mutex lock failed", ret);
    }
    return ret;
}
inline void Mutex::unlock()
{
    int ret;
    ret = pthread_mutex_unlock(&m_lock);
    if (0 != ret)
    {
        throw SyncException("Mutex unlock failed", ret);
    }
}
inline int Mutex::tryLock()
{
    int ret = 0;
    ret = pthread_mutex_trylock(&m_lock);
    if (0 != ret)
    {
        if (EBUSY == ret)
        {
            return ret;
        }
        throw SyncException("Mutex trylock failed", ret);
    }
    return ret;
}
inline Mutex::operator pthread_mutex_t*()
{
    return &m_lock;
}

inline CondVarAttributes::operator pthread_condattr_t*()
{
    return &m_condAttr;
}

inline void CondVar::lock()
{
    m_lock.lock();
}
inline void CondVar::unlock()
{
    m_lock.unlock();
}
inline void CondVar::wait()
{
    int ret = 0;
    ret = pthread_cond_wait(&m_cond, m_lock);
    if (ret != 0 && ret != EINTR)
    {
        throw SyncException("Cond wait failed", ret);
    }
}
inline int CondVar::wait(int uSec)
{
    int ret = 0;
    struct timespec absTime;
    TimeVal tv;
    tv.now().addUSec(uSec);
    tv.toTimeSpec(absTime);

    ret = pthread_cond_timedwait(&m_cond, m_lock, &absTime);
    if (ret != 0)
    {
        if (ETIMEDOUT == ret)
        {
            return ret;
        }
        throw SyncException("Cond wait failed", ret);
    }

    return ret;
}
inline void CondVar::signal()
{
    int ret = 0;
    ret = pthread_cond_signal(&m_cond);
    if (ret != 0)
    {
        throw SyncException("Cond Signal failed", ret);
    }
}
inline void CondVar::broadcast()
{
    int ret = 0;
    ret = pthread_cond_broadcast(&m_cond);
    if (ret != 0)
    {
        throw SyncException("Cond Broadcast failed", ret);
    }
}
inline Mutex& CondVar::mutex()
{
    return m_lock;
}


class Futex
{
 public:
    typedef ScopedLock<Futex> ScopedFutex;

    enum
    {
        DEFAULT_WAKE_THREADS = 1,
    };

    Futex()
        : m_futex(UNLOCKED)
    {
    }

    // In a non-contended case, only one atomic compare operation, no context
    // switching to kernel.
    void lock()
    {
        int c;
        // This is implemented as specified in "Futexes are Tricky"
        // If the futex state is Unlocked, change its state to LockedNoWaiters,
        // then exit
        if ((c = m_futex.CompareAndSwap(UNLOCKED, LOCKED_NO_WAITERS)) != UNLOCKED)
        {
            if (c != LOCKED_WITH_WAITERS)
            {
                // futex is locked with no waiters already, now we are
                // requesting for a lock, change the state to LockWithWaiters
                c = m_futex.Swap(LOCKED_WITH_WAITERS);
            }

            while(c != UNLOCKED)
            {
                // futex is now locked with waiters, that includes me
                // Wait till the lock is released
                this->wait(LOCKED_WITH_WAITERS);

                // Fuxtex value might have been changed by other threads
                // So wait till it is unlocked
                c = m_futex.Swap(LOCKED_WITH_WAITERS);
            }
        }
    }

    void unlock()
    {
        // If there are no waiters, no need to wake anybody
        if (LOCKED_NO_WAITERS != m_futex--)
        {
            m_futex = UNLOCKED;
            this->wake();
        }
    }

 protected:
    // Futex states
    enum
    {
        UNLOCKED = 0,
        LOCKED_NO_WAITERS = 1,
        LOCKED_WITH_WAITERS = 2,
    };

    int wait(int val)
    {
        int ret = SysFutex(&m_futex, FUTEX_WAIT, val);
        if (ret != 0)
        {
            if (errno == EWOULDBLOCK || errno == EINTR)
            {
                return ret;
            }
            throw SyncException("Futex wait failed");
        }
        return ret;
    }
    int wait(int val, int usecTimeout)
    {
        struct timespec absTime;
        TimeVal tv;
        tv.now().addUSec(usecTimeout);
        tv.toTimeSpec(absTime);

        int ret = SysFutex(&m_futex, FUTEX_WAIT, val, &absTime);
        if (ret != 0)
        {
            if (ret == EWOULDBLOCK || ret == EINTR || ret == ETIMEDOUT)
            {
                return ret;
            }
            throw SyncException("Futex wait failed", ret);
        }
    }

    // To wakeup all threads pass INT_MAX
    // Returns the no. of processes wokenup
    int wake(int wakeThreads = DEFAULT_WAKE_THREADS)
    {
        return SysFutex(&m_futex, FUTEX_WAKE, wakeThreads);
    }

    void wakeOp()
    {
    }

    // Useful for condition variable wakeup
    // move threads from condFutex to mutexFutex
    // Avoids cache line ping-pongs
    void cmpRequeue()
    {
    }

     static int SysFutex(int *uaddr, int op, int val,
             const struct timespec *timeout = NULL,
             int *uaddr2 = NULL, int val3 = 0)
     {
         return syscall(__NR_futex, uaddr, op, val, timeout, uaddr2, val3);
     }

 private:
    Atomic<int> m_futex;

};

class RWLock
{
 public:
    RWLock()
    {
        int ret = pthread_rwlock_init(&m_rwLock, NULL);
        if (ret)
        {
            throw SyncException("RWLock init failed", ret);
        }
    }
    ~RWLock()
    {
        pthread_rwlock_destroy(&m_rwLock);
    }

    void ReadLock()
    {
        int ret = pthread_rwlock_rdlock(&m_rwLock);
        if (ret)
        {
            throw SyncException("RWLock read lock failed", ret);
        }
    }
    bool TryReadLock()
    {
        int ret = pthread_rwlock_tryrdlock(&m_rwLock);
        if (ret != 0)
        {
            if (ret == EBUSY)
            {
                return false;
            }
            throw SyncException("RWLock try read lock failed", ret);
        }
        return true;
    }

    void Unlock()
    {
        int ret = pthread_rwlock_unlock(&m_rwLock);
        if (ret != 0)
        {
            throw SyncException("RWLock unlock failed", ret);
        }
    }

    void WriteLock()
    {
        int ret = pthread_rwlock_wrlock(&m_rwLock);
        if (ret != 0)
        {
            throw SyncException("RWLock write lock failed", ret);
        }
    }

    bool TryWriteLock()
    {
        int ret = pthread_rwlock_trywrlock(&m_rwLock);
        if (ret != 0)
        {
            if (ret == EBUSY)
            {
                return false;
            }
            throw SyncException("RWLock try write lock failed", ret);
        }
        return true;
    }


 protected:
    pthread_rwlock_t    m_rwLock;
};

class ScopedReadLock
{
 public:
    ScopedReadLock(RWLock& m)
        : m_lock(&m)
    {
        m_lock->ReadLock();
    }
    inline void Unlock()
    {
        m_lock->Unlock();
        m_lock = NULL;
    }
    ~ScopedReadLock()
    {
        if (m_lock)
        {
            m_lock->Unlock();
        }
    }
 private:
    RWLock* m_lock;
};

class ScopedWriteLock
{
 public:
    ScopedWriteLock(RWLock& m)
        : m_lock(&m)
    {
        m_lock->WriteLock();
    }
    inline void Unlock()
    {
        m_lock->Unlock();
        m_lock = NULL;
    }
    ~ScopedWriteLock()
    {
        if (m_lock)
        {
            m_lock->Unlock();
        }
    }
 private:
    RWLock* m_lock;
};

}//namespace eAccelero

#endif // __EACC_Sync_h__
