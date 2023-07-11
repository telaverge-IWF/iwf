#ifndef __EACC_MemPool_h__
#define __EACC_MemPool_h__

#include "Allocator.h"

namespace eAccelero
{

enum
{
    MAX_MEM_POOL_BITS = 3,
    MAX_MEM_POOLS = 1 << MAX_MEM_POOL_BITS,
    MAX_INT_BITS = sizeof(unsigned)*8,
};

struct MemPoolHintEntry
{
    unsigned chunkSize;
    uint16_t poolSize;
    uint16_t maxPools;
};
struct MemPoolHint
{
    MemPoolHintEntry hints[MAX_MEM_POOLS];
};

class MemPool
{
 public:
    enum
    {
        INVALID_BIN = MAX_MEM_POOLS,
        INVALID_IDX = 0xFFFFFFFF,
    };
    
    MemPool(const MemPoolHint &hint = DEFAULT_MEMPOOL_HINT);
    
    ~MemPool();
    
    void *Alloc(unsigned sz, unsigned *idx = NULL);
    
    void Free(void *ptr);
    
    void* operator[](unsigned idx)
    {
        unsigned bin = IndexAllocatorImpl::GetUserBits(idx);
        if (bin >= MAX_MEM_POOLS)
        {
            throw std::out_of_range("Invalid bin size");
        }
        return (*m_bins[bin])[idx];
    }
    void* Find(unsigned idx)
    {
        unsigned bin = IndexAllocatorImpl::GetUserBits(idx);
        if (bin >= MAX_MEM_POOLS)
        {
            throw std::out_of_range("Invalid bin size");
        }
        return m_bins[bin]->find(idx);
    }    
    unsigned count()
    {
        return m_allocCount;
    }
    
    unsigned BinSize(unsigned bin)
    {
        return m_hint.hints[bin].chunkSize;
    }
    
    static MemPoolHint DEFAULT_MEMPOOL_HINT;
    
 protected:
    unsigned Fit(unsigned sz);

 private:
    unsigned m_allocCount;
    // unsigned m_bitmap[MAX_INT_BITS];
    MemPoolHint m_hint;
    struct Range
    {
        unsigned start;
        unsigned end;
    } m_range[MAX_MEM_POOLS];
    
    IndexAllocatorImpl *m_bins[MAX_MEM_POOLS];
};

} // namespace eAccelero

#endif // __EACC_MemPool_h__