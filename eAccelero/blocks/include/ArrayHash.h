#ifndef __EACC_ArrayHash_h__
#define __EACC_ArrayHash_h__

#include <stdexcept>

namespace eAccelero
{

class ArrayHashImpl
{
 public:
    enum
    {
        DEFAULT_POOL_SIZE = 128,
        DEFAULT_MAX_POOLS = 2
    };

    // Poolsize should be a power of 2
    ArrayHashImpl(unsigned poolSize = DEFAULT_POOL_SIZE,
                  unsigned maxPools = DEFAULT_MAX_POOLS)
        : m_poolSize(poolSize),
          m_maxPools(maxPools),
          m_mask(poolSize -1),
          m_shift(__builtin_ctz(m_poolSize))
    {
        if (!m_poolSize && (m_poolSize & m_mask) != 0)
            throw std::out_of_range("Pools size must be power of 2");

        m_array = (void***)calloc(maxPools, sizeof(void**));
        InitPool(0);
    }

    const void*& operator[](unsigned index) const
    {
        unsigned poolIndex = (index & ~m_mask ) >> m_shift;
        if (poolIndex >= m_maxPools)
            throw std::out_of_range("Index exceeds max pools");
        if (!m_array[poolIndex])
            throw std::out_of_range("Pool not allocated");
        return (const void*&)m_array[poolIndex][index & m_mask];
    }

    void*& operator[](unsigned index)
    {
        unsigned poolIndex = (index & ~m_mask ) >> m_shift;
        if (poolIndex >= m_maxPools)
            throw std::out_of_range("Index exceeds max pools");
        if (!m_array[poolIndex])
            InitPool(poolIndex);
        return m_array[poolIndex][index & m_mask];
    }

 protected:

    void InitPool(unsigned index)
    {
        if (index >= m_maxPools)
            throw std::out_of_range("Cannot allocate more pools");
        if (m_array[index]) // already allocated
            return;
        m_array[index] = (void**)calloc(m_poolSize, sizeof(void*));
    }

 private:
    void ***m_array;

    unsigned m_poolSize;
    unsigned m_maxPools;
    unsigned m_mask;
    unsigned m_shift;
};

};

#endif // __EACC_ArrayHash_h__
