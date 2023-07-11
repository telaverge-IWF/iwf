#ifndef __EACC_Atomic_h__
#define __EACC_Atomic_h__

#include <stdint.h>

namespace eAccelero
{
// GCC specific version 4.1.x required

// T can be only int or long or long long
// For lock free operations
template <typename T = int>
class Atomic
{
 public:
    Atomic()
        : m_val(0)
    {
    }
    
    explicit Atomic(T val)
        : m_val(val)
    {
    }
    explicit Atomic(const Atomic &rhs)
    {
        m_val = rhs.m_val;
    }

    inline void operator =(T val)
    {
        m_val = val;
    }
    inline void operator =(const Atomic &rhs)
    {
        m_val = rhs.m_val;
    }
    inline operator const T&() const
    {
        return m_val;
    }

    // TODO volatile variants

    inline T operator++() // prefix
    {
        return __sync_add_and_fetch(&m_val, 1);
    }
    inline T operator++(int) // postfix
    {
        return __sync_fetch_and_add(&m_val, 1);
    }
    inline T operator+=(T i) 
    {
        return __sync_add_and_fetch(&m_val, i);
    }

    inline T operator--() //prefix
    {
        return __sync_sub_and_fetch(&m_val, 1);
    }
    inline T operator--(int) // postfix
    {
        return __sync_fetch_and_sub(&m_val, 1);
    }
    inline T operator-=(T i) 
    {
        return __sync_sub_and_fetch(&m_val, i);
    }

    inline T operator&=(T i) 
    {
        return __sync_and_and_fetch(&m_val, i);
    }
    inline T operator|=(T i) 
    {
        return __sync_or_and_fetch(&m_val, i);
    }
    inline T operator^=(T i) 
    {
        return __sync_xor_and_fetch(&m_val, i);
    }

    inline bool operator ==(const Atomic& rhs)
    {
        return (m_val == rhs.m_val);
    }
    inline bool operator ==(const T& rhs)
    {
        return (m_val == rhs);
    }

    // If the m_val == oldVal then m_val is newVal and return oldVal
    inline T CompareAndSwap(T oldVal, T newVal)
    {
        return __sync_val_compare_and_swap(&m_val, oldVal, newVal);
    }

    // Returns the oldval an sets this object with newVal
    inline T Swap(T newVal)
    {
        return __sync_lock_test_and_set(&m_val, newVal);
    }

    T* operator&()
    {
        return &m_val;
    }
 private:
    T m_val;
};

} // namespace eAccelero

#endif // __EACC_Atomic_h__
