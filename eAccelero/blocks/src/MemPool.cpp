#include "MemPool.h"
#include <limits.h>

namespace eAccelero
{

MemPoolHint MemPool::DEFAULT_MEMPOOL_HINT = 
                    {{ 
                        {64, 256, 128},
                        {128, 512, 128},
                        {256, 512, 128},
                        {512, 512, 128},
                        {2048, 128, 128},
                        {4096, 64, 128},
                        {8192, 32, 64},
                        //max size of this array is 8
                        //so changed 16384 to 32768
                        {32768, 32, 64}
                     }};
    
MemPool::MemPool(const MemPoolHint &hint)
    : m_allocCount(0)
{
    int i;
    memcpy(&m_hint, &hint, sizeof(m_hint));
    
    // Populate the bins
    for (i = 0; i < MAX_MEM_POOLS; i++)
    {
        m_bins[i] = new IndexAllocatorImpl(hint.hints[i].chunkSize,
                                           hint.hints[i].poolSize,
                                           hint.hints[i].maxPools);
    }
    
    unsigned prevSz = 0;
    for(int i = 0; i < MAX_MEM_POOLS; i++)
    {
        m_range[i].start = prevSz;
        m_range[i].end = m_hint.hints[i].chunkSize;
        prevSz = m_range[i].end;
    }    
#if 0    
    // Populate the bitmap, this will be used while allocating
    unsigned sz = hint.hints[0].chunkSize;
    int hintIndex = 0;    
    for (i = 0; i < MAX_INT_BITS; i++)
    {
        if ( (1 << i) > sz)
        {
            hintIndex++;
            if (hintIndex < MAX_MEM_POOLS)
            {
                sz = hint.hints[hintIndex].chunkSize;
            }
            else
            {
                // Set to a larger value so it doesn't enter this condition
                // The bitmap for subsequent values will be set to MAX_POOLS
                sz = UINT_MAX;
            }
        }
        m_bitmap[i] = hintIndex;        
    }
#endif
}
    
MemPool::~MemPool()
{
    for (int i = 0; i < MAX_MEM_POOLS; i++)
    {
        delete m_bins[i];
    }    
}
    
void *MemPool::Alloc(unsigned sz, unsigned *idx)
{
    unsigned bin = this->Fit(sz);
    if (bin == MAX_MEM_POOLS)
    {
        throw std::out_of_range("No bins of requested size");
    }
    // The last few bits of the index is used to store the bin id
    // This will be reset on free    
    void *ptr = m_bins[bin]->alloc(idx, bin);
    
    m_allocCount++;
    
    return ptr;
}
    
void MemPool::Free(void *ptr)
{
    unsigned bin = IndexAllocatorImpl::GetUserBits(ptr);
    if (bin >= MAX_MEM_POOLS)
    {
        throw std::out_of_range("No bins of requested size");
    }

    m_bins[bin]->free(ptr);
    
    m_allocCount--;
}

unsigned MemPool::Fit(unsigned sz)
{
    int low = 0;
    int up = MAX_MEM_POOLS - 1;
    int ind = (up - low) >> 1;

    while(1)
    {
        if (m_range[ind].start < sz && m_range[ind].end >= sz)
        {
            break;
        }
        if (sz == m_range[ind].start)
        {
            ind--;
            break;
        }
        if (sz > m_range[ind].end)
        {
            low = ind + 1;
        }
        else
        {   
            up = ind - 1;
        }
        if (up < low)
        {
            ind = MAX_MEM_POOLS;
            break;
        }
        ind = low + ((up - low) >> 1);
    }

    return ind;
    
#if 0        
    return m_bitmap[MAX_INT_BITS - __builtin_clz(sz-1)];
#endif
}
}
