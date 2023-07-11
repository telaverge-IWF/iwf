#ifndef __EACC_Ref_h__
#define __EACC_Ref_h__

#include "Atomic.h"
#include "Exception.h"

#ifdef REF_DEBUG_BT
#include <execinfo.h>
#include <vector>
#include <Sync.h>
#include <iostream>

#include <execinfo.h>
#include <vector>
#include <Sync.h>
#include <iostream>
#endif // REF_DEBUG_BT

namespace eAccelero
{

EACC_DEFINE_EXCEPTION_CLASS(NullPtrException, Exception, "NULL Pointer Exception");

#ifdef REF_DEBUG_BT
class Backtrace
{
 public:
    enum
    {
        MAX_BT = 16
    };

    Backtrace(int refCount, bool dup = true)
        : m_refCount(refCount),
          m_dup(dup),
          nptrs(0)
    {
        nptrs = backtrace(ptrs, MAX_BT);
    }

    void dump()
    {
        std::cout << "RefCount: " << m_refCount << " Dup: " << m_dup << std::endl;
        for (int i = 0; i < nptrs; i++)
        {
            std::cout << ptrs[i] << std::endl;
        }
    }

    int m_refCount;
    bool m_dup;
    void *ptrs[MAX_BT];
    int nptrs;
};

class BacktraceInfo
{
 public:
    ~BacktraceInfo()
    {
        for(std::vector<Backtrace*>::iterator it = btList.begin();
            it != btList.end(); it++)
        {
            delete *it;
        }
    }

    void LogBT(int refCount, bool dup = true)
    {
        Mutex::ScopedMutex guard(m_lock);
        btList.push_back(new Backtrace(refCount, dup));
    }

    void dump(void* ptr)
    {
        Mutex::ScopedMutex guard(m_lock);
        std::cout << "======= Ref Obj: " << ptr << std::endl;
        for(std::vector<Backtrace*>::iterator it = btList.begin();
            it != btList.end(); it++)
        {
            (*it)->dump();
        }
        std::cout << "=======\n";
    }

    Mutex m_lock;
    std::vector<Backtrace*> btList;
};

#endif // REF_DEBUG_BT

template <class DP>
class RefObj;

struct DefaultRefDelPolicy
{
    static void Delete(RefObj<DefaultRefDelPolicy>* obj);
};

// A reference counted object
template <class DP = DefaultRefDelPolicy>
class RefObj
{
 public:
#ifndef REF_DEBUG_BT
    RefObj()
        : m_counter(1)
    {
    }
#else
    RefObj(bool debugEnable = false)
        : m_counter(1)
          m_debugEnable(debugEnable)
    {
        if (m_debugEnable) m_debugBT.LogBT(1);
    }
#endif

    // Increment the reference
    void Duplicate()
    {
#ifndef REF_DEBUG_BT
        m_counter++;
#else
        int local = ++m_counter;
        if (m_debugEnable) m_debugBT.LogBT(local+1);
#endif
    }

    // Decrement the reference. On 0 delete the pointer
    // This object is invalid after the deletion occurs, so care must be taken
    // 0 Return value means the object is deleted
    int Release()
    {
        int local;
        if ((local = --m_counter) == 0)
        {
#ifdef REF_DEBUG_BT
            if (m_debugEnable) {
                m_debugBT.LogBT(local, false);
                m_debugBT.dump(this);
            }
#endif
            DP::Delete(this);
            return 0;
        }

#ifdef REF_DEBUG_BT
        if (m_debugEnable) m_debugBT.LogBT(local, false);
#endif

        return local;
    }
    int RefCount()
    {
        return m_counter;
    }

    virtual ~RefObj()
    {
    }
 private:
    // Reference counted objects should use Ref to copy
    RefObj(const RefObj&) {}
    RefObj& operator =(const RefObj&) { return *this;}
    
    // mutex not required, the counter is atomic
    mutable Atomic<> m_counter;

#ifdef REF_DEBUG_BT
    bool m_debugEnable;
    BacktraceInfo m_debugBT;
#endif
};

template <typename C>
struct DefaultRefRP
{
    inline static int Release(C *obj)
    {
        return obj->Release();
    }
};

template <typename C, class RP = DefaultRefRP<C> >
class Reference
{
 public:
    Reference()
        : m_ptr(NULL)
    {
    }
    // The ownership is now with the Reference obj
    Reference(C *ptr)
        : m_ptr(ptr)
    {
    }
    Reference(const Reference& ref)
        : m_ptr(ref.m_ptr)
    {
        if (m_ptr) m_ptr->Duplicate();
    }
    template <class Other>
    Reference(const Reference<Other>& ref)
        : m_ptr(ref.m_ptr)
    {
        if (m_ptr) m_ptr->Duplicate();
    }

    ~Reference()
    {
        if (m_ptr)
        {
            RP::Release(m_ptr);
        }
    }

    Reference& operator = (C *ptr)
    {
        if (m_ptr != ptr)
        {
            if (m_ptr) RP::Release(m_ptr);
            m_ptr = ptr;
        }
        return *this;
    }
    Reference& operator = (const Reference& ref)
    {
        if (&ref != this)
        {
            if (m_ptr) RP::Release(m_ptr);
            m_ptr = ref.m_ptr;
            if (m_ptr) m_ptr->Duplicate();
        }
        return *this;
    }
    template <class Other>
    Reference& operator = (const Reference<Other>& ref)
    {
        if (&ref != this)
        {
            if (m_ptr) RP::Release(m_ptr);
            m_ptr = ref.m_ptr;
            if (m_ptr) m_ptr->Duplicate();
        }
        return *this;
    }

    C* Ptr()
    {
        return m_ptr;
    }
    const C* Ptr() const
    {
        return m_ptr;
    }

    const C* Get() const
    {
        if (!m_ptr)
        {
            throw NullPtrException("Ref ptr NULL");
        }
        return m_ptr;
    }
    C* Get()
    {
        if (!m_ptr)
        {
            throw NullPtrException("Ref ptr NULL");
        }
        return m_ptr;
    }

    const C* operator -> () const
    {
        return this->Get();
    }
    C* operator -> ()
    {
        return this->Get();
    }

    const C& operator *() const
    {
        return *(this->Get());
    }
    C& operator *()
    {
        return *(this->Get());
    }

    operator const C*() const
    {
        return m_ptr;
    }
    operator C*()
    {
        return m_ptr;
    }

    bool operator !()
    {
        return m_ptr == NULL;
    }
    bool IsNull()
    {
        return m_ptr == NULL;
    }
    bool operator == (const Reference& ref) const
    {
        return m_ptr == ref.m_ptr;
    }
    bool operator != (const Reference& ref) const
    {
        return m_ptr != ref.m_ptr;
    }
    
    void swap(Reference& ref)
    {
        std::swap(m_ptr, ref.m_ptr);
    }

 private:
    C *m_ptr;
};


// For pointers that don't derive from RefObj
class ReferenceCounter
{
 public:
    ReferenceCounter()
        : m_counter(1)
    {
    }
    ~ReferenceCounter()
    {
    }

    // Increment the reference
    void Duplicate()
    {
        m_counter++;
    }

    // Decrement the reference. On 0 delete the pointer
    int Release()
    {
        return --m_counter;
    }
    int RefCount()
    {
        return m_counter;
    }

 private:
    Atomic<> m_counter;
};

template <typename C>
struct DefSPDelPolicy
{
    inline static void Delete(C *obj)
    {
        if (obj)
        {
            delete obj;
        }
    }
};

template <typename C, class DP = DefSPDelPolicy<C> >
class SmartPtr
{
 public:
    SmartPtr()
        : m_ptr(NULL),
          m_rc(new ReferenceCounter())
    {
    }
    // The ownership is now with the SmartPtr obj
    SmartPtr(C *ptr)
        : m_ptr(ptr),
          m_rc(new ReferenceCounter())
    {
    }
    SmartPtr(const SmartPtr& ref)
        : m_ptr(ref.m_ptr),
          m_rc(ref.m_rc)
    {
        m_rc->Duplicate();
    }
    template <class Other>
    SmartPtr(const SmartPtr<Other>& ref)
        : m_ptr(ref.m_ptr),
          m_rc(ref.m_rc)
    {
        m_rc->Duplicate();
    }

    ~SmartPtr()
    {
        this->Release();
    }
    void Release()
    {
        if (m_rc->Release() == 0)
        {
            DP::Delete(m_ptr);
            m_ptr = NULL;
            delete m_rc;
            m_rc = NULL;
        }
    }

    SmartPtr& operator = (C *ptr)
    {
        if (m_ptr != ptr)
        {
            ReferenceCounter *tempRC = new ReferenceCounter();
            this->Release();
            m_ptr = ptr;
            m_rc  = tempRC;
        }
        return *this;
    }
    SmartPtr& operator = (const SmartPtr& ref)
    {
        if (&ref != this)
        {
            SmartPtr temp(ref);
            this->swap(temp);
        }
        return *this;
    }
    template <class Other>
    SmartPtr& operator = (const SmartPtr<Other>& ref)
    {
        if (&ref != this)
        {
            SmartPtr temp(ref);
            this->swap(temp);
        }
        return *this;
    }

    C* Ptr()
    {
        return m_ptr;
    }
    const C* Ptr() const
    {
        return m_ptr;
    }

    const C* Get() const
    {
        if (!m_ptr)
        {
            throw NullPtrException("Null smartptr");
        }
        return m_ptr;
    }
    C* Get()
    {
        if (!m_ptr)
        {
            throw NullPtrException("Null smartptr");
        }
        return m_ptr;
    }

    const C* operator -> () const
    {
        return this->Get();
    }
    C* operator -> ()
    {
        return this->Get();
    }

    const C& operator *() const
    {
        return *(this->Get());
    }
    C& operator *()
    {
        return *(this->Get());
    }

    operator const C*() const
    {
        return m_ptr;
    }
    operator C*()
    {
        return m_ptr;
    }

    bool operator !()
    {
        return m_ptr == NULL;
    }
    bool IsNull()
    {
        return m_ptr == NULL;
    }
    bool operator == (const SmartPtr& ref) const
    {
        return m_ptr == ref.m_ptr;
    }
    bool operator != (const SmartPtr& ref) const
    {
        return m_ptr != ref.m_ptr;
    }
    
    void swap(SmartPtr& ref)
    {
        std::swap(m_ptr, ref.m_ptr);
        std::swap(m_rc, ref.m_rc);
    }

 private:
    C *m_ptr;
    ReferenceCounter *m_rc;
};

inline void DefaultRefDelPolicy::Delete(RefObj<DefaultRefDelPolicy>* obj)
{
    delete obj;
}

};

#endif // __EACC_PTR_H__
