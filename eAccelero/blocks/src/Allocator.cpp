#include "Allocator.h"
#include <stdlib.h>
#include <assert.h>

namespace eAccelero
{

Pool::Pool(unsigned entrySize, unsigned poolSize, unsigned poolIdx)
    : m_chunks(NULL),
      m_chunkSize(0),
      m_poolIdx(poolIdx),
      m_poolSize(poolSize)
{
    ChunkHeader *cptr = NULL;
    unsigned idx = 0;
    m_chunkSize = entrySize + sizeof(ChunkHeader);

    m_chunks = calloc(poolSize, m_chunkSize);
    for (unsigned i = 0; i < poolSize; i++)
    {
        idx = i + (poolSize * poolIdx);
        cptr = (*this)[i];
        cptr->idx = idx;
        cptr->nextIdx = idx + 1;
    }
    cptr->nextIdx = IndexAllocatorImpl::INVALID_IDX;
}

Pool::~Pool()
{
    if (m_chunks)
    {
        free(m_chunks);
    }
}

IndexAllocatorImpl::IndexAllocatorImpl(unsigned entrySize, 
               unsigned poolSize,
               unsigned maxPools,
               bool fixedSize)
    : m_poolSize(poolSize),
      m_maxPools(maxPools),
      m_fixedSize(fixedSize),
      m_chunkSize(entrySize),
      m_pools(NULL),
      m_poolCount(0),
      m_allocCount(0),
      m_firstFreeIdx(INVALID_IDX),
      m_lastFreeIdx(INVALID_IDX)
{
    m_pools = new Pool*[m_maxPools];

    for (unsigned i = 0; i < m_maxPools; i++)
    {
        m_pools[i] = NULL;
    }

    this->allocPool();
}

IndexAllocatorImpl::~IndexAllocatorImpl()
{
    Mutex::ScopedMutex guard(m_guard);
    for (unsigned i = 0; i < m_poolCount; i++)
    {
        if (m_pools[i])
        {
            delete m_pools[i];
        }
    }
    delete[] m_pools;
}

void IndexAllocatorImpl::allocPool()
{
    if (m_maxPools == m_poolCount)
    {
        if (m_fixedSize)
        {
            throw std::bad_alloc();
        }
        unsigned i;
        m_maxPools += m_poolCount;

        // Resize the pool exponentially and copy the old contents to the new
        // allocated pool
        Pool** tempPools = new Pool*[m_maxPools];
        for (i = 0; i < m_poolCount; i++)
        {
            tempPools[i] = m_pools[i];
        }
        for (; i < m_maxPools; i++)
        {
            tempPools[i] = NULL;
        }
        delete []m_pools;
        m_pools = tempPools;
    }
    EACC_ASSERT(m_pools[m_poolCount] == NULL);

    m_pools[m_poolCount] = new Pool(m_chunkSize, m_poolSize, m_poolCount);
    m_firstFreeIdx = m_poolCount * m_poolSize;
    m_lastFreeIdx = ((m_poolCount + 1) * m_poolSize) - 1;
    m_poolCount++;
}

void* IndexAllocatorImpl::alloc(unsigned *idx, unsigned userBits)
{
    Mutex::ScopedMutex guard(m_guard);
    
    if (m_firstFreeIdx == INVALID_IDX)
    {
        // No more free entries in all the currently allocated pools
        // try allocating a new pool
        this->allocPool();
    }

    Pool::ChunkHeader* cptr = this->Get(m_firstFreeIdx);
    m_firstFreeIdx = cptr->nextIdx;

    cptr->nextIdx = INDEX_ALLOCED;
    if (idx)
    {
       IncGen(cptr->idx);
       *idx = SetUserBits(cptr->idx, userBits);
    }

    if (m_firstFreeIdx == INVALID_IDX)
    {
        // no more free entries in the currently allocated pools
        m_lastFreeIdx = INVALID_IDX;
    }
    m_allocCount++;

    return chunkToData(cptr);
}

void IndexAllocatorImpl::free(void *data)
{
    Mutex::ScopedMutex guard(m_guard);
    Pool::ChunkHeader* cptr = dataToChunk(data);

    if (GetIdx(cptr->idx) >= (m_poolSize * m_poolCount))
    {
        throw std::out_of_range("IndexAllocator: Freeing invalid index");
    }
    if (cptr->nextIdx != INDEX_ALLOCED)
    {
        throw std::out_of_range("IndexAllocator Free: Entry not allocated");
    }
    cptr->nextIdx = INVALID_IDX;
    cptr->idx &= ~USER_BIT_MASK; // reset the user portion of the index

    if (m_firstFreeIdx == INVALID_IDX)
    {
        // Empty list
        m_firstFreeIdx = cptr->idx;
    }
    else
    {
        this->Get(m_lastFreeIdx)->nextIdx = cptr->idx;
    }
    m_lastFreeIdx = cptr->idx;

    m_allocCount--;
}

std::ostream& operator << (std::ostream& os, const Pool& pool)
{
    Pool::ChunkHeader* cptr;
    os << "  Pool[" << pool.m_poolIdx << "]" << std::endl;
    os << "  {" << std::endl;
    for(unsigned i = 0; i < pool.m_poolSize; i++)
    {
        cptr = (const_cast<Pool&>(pool))[i];
        os << "    idx -> " << cptr->idx << ", next ->" << cptr->nextIdx 
           << std::endl;
    }
    os << "  }" << std::endl;

    return os;
}

std::ostream& operator << (std::ostream& os, const IndexAllocatorImpl& table)
{
    os << "Alloc Count = " << table.m_allocCount << std::endl;
    os << "Pool Size   = " << table.m_poolSize << std::endl;
    os << "Max Pools   = " << table.m_maxPools << std::endl;
    os << "Chunk Size  = " << table.m_chunkSize << std::endl;
    os << "Pools Count = " << table.m_poolCount << std::endl;
    os << "[ Free Idx =" << table.m_firstFreeIdx << ", Last idx = "
       << table.m_lastFreeIdx << "]" << std::endl;
    for (unsigned i = 0; i < table.m_poolCount; i++)
    {
        os << *table.m_pools[i];
    }

    return os;
}

} // namespace eAccelero
