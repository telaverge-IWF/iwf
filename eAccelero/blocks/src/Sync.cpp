
#include <Sync.h>

namespace eAccelero
{

MutexAttributes::MutexAttributes(int type,
        int processShared)
{
    int ret;
    ret = pthread_mutexattr_init(&m_attr);
    if (ret != 0)
    {
        throw SyncException("MutexAttr init failed", ret);
    }        

    if (type != PTHREAD_MUTEX_DEFAULT)
    {
        ret = pthread_mutexattr_settype(&m_attr, type);
        if (ret != 0)
        {
            throw SyncException("Unable to set Mutex attr type", ret);
        }
    }
    if (processShared != PTHREAD_PROCESS_PRIVATE)
    {
        ret = pthread_mutexattr_setpshared(&m_attr, processShared);
        if (ret != 0)
        {
            throw SyncException("Unable to set Mutex attr type", ret);
        }
    }
}

MutexAttributes::~MutexAttributes()
{
    int ret;
    ret = pthread_mutexattr_destroy(&m_attr);
    if (ret != 0)
    {
        throw SyncException("MutexAttr destroy failed", ret);
    }        
}

Mutex::Mutex(int type)
{
    int ret;
    MutexAttributes attr(type);
    ret = pthread_mutex_init(&m_lock, attr);
    if (0 != ret)
    {
        throw SyncException("Mutex init failed", ret);
    }
}
Mutex::Mutex(MutexAttributes& attr)
{
    int ret;

    ret = pthread_mutex_init(&m_lock, attr);
    if (0 != ret)
    {
        throw SyncException("Mutex init failed", ret);
    }
}
Mutex::~Mutex()
{
    int ret;

    ret = pthread_mutex_destroy(&m_lock);
    if (0 != ret)
    {
        throw SyncException("Mutex destroy failed", ret);
    }
}

CondVarAttributes::CondVarAttributes(int processShared)
{
    int ret = 0;
    ret = pthread_condattr_init(&m_condAttr);
    if (ret != 0)
    {
        throw SyncException("CondAttr init failed", ret);
    }
    if (processShared != PTHREAD_PROCESS_PRIVATE)
    {
        ret = pthread_condattr_setpshared(&m_condAttr, processShared);
        if (ret != 0)
        {
            throw SyncException("CondAttr set shared failed", ret);
        }
    }
}

CondVarAttributes::~CondVarAttributes()
{
    int ret = 0;
    ret = pthread_condattr_destroy(&m_condAttr);
    if (ret != 0)
    {
        throw SyncException("CondAttr destroy failed", ret);
    }
}

CondVar::CondVar()
{
    int ret;
    ret = pthread_cond_init(&m_cond, NULL);
    if (ret < 0)
    {
        throw SyncException("Cond Initializer failed", ret);
    }
}
CondVar::CondVar(MutexAttributes& lAttr, CondVarAttributes& cvAttr)
    : m_lock(lAttr)
{
    int ret;

    ret = pthread_cond_init(&m_cond, cvAttr);
    if (ret != 0)
    {
        throw SyncException("Cond Initializer failed", ret);
    }        
}
CondVar::~CondVar()
{
    int ret;
    ret = pthread_cond_destroy(&m_cond);
    if (ret != 0)
    {
        throw SyncException("Cond Destroy failed", ret);
    }
}


} // namespace eAccelero
