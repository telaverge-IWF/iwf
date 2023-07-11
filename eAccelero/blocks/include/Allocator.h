#ifndef __EACC_Allocator_h__
#define __EACC_Allocator_h__


#include "Exception.h"
#include <ostream>
#include <stdexcept>
#include "Sync.h"

namespace eAccelero
{

/**
 * @file Allocator.h
 * An indexed allocator allocates fixed chunks of pre allocated memory. This
 * will be useful for structures/classes whose size is fixed and known during
 * the compile time.
 * The advantages in using an indexed allocator over malloc/new are as follows
 *  - Since the allocated size is know beforehand, memory fragmentation will
 *    not exists
 *  - Where there are lots of memory chunks allocated, malloc/new takes more 
 *    time allocation and freeing memory. In the indexed allocator, the memory
 *    allocation and deletion is a constant time operation
 *  - When a memory is allocated, a unique integer indentifier is returned,
 *    and this memory is addressable using the unique integer. Will be useful 
 *    in case where a unique id is required for transactional data.
 *  - Useful for shared memory allocation where the allocated index can be 
 *    maintained, instead of the address. When shared across processes the 
 *    addresses can change.
 * 
 * The Allocator consists of a set of pools, each pool with a specified number
 * of chunks. The chunk portion will be allocated and returned when the 
 * allocation request is made. The Allocator also maintain a list of free chunks
 * that are available for allocation. Each chunk has a chunk header, having the
 * index of the chunk and index to the next free chunk. When the chunk is 
 * allocated, nextIdx is used to indicate that the chunk is allocated. For
 * each chunk the memory overhead will be 8 bytes.
 */

class Pool;
std::ostream& operator << (std::ostream& os, const Pool& pool);

class Pool
{
 public:
    // Can be further optimized by maintining next and prev for free list
    // When allocated, the current idx can be obtained from the next->prev
    //  and the whole chunk can be used for data (no need to prev/next)
    // But might have debugging issues.
    struct ChunkHeader
    {
        unsigned idx;     // Index position in the table
        unsigned nextIdx; // Used when free, to maintain the free list
    };

    Pool(unsigned chunkSize, unsigned poolSize, unsigned poolIdx);
    ~Pool();

    ChunkHeader* operator [](unsigned idx)
    {
        if (idx >= m_poolSize)
        {
            throw std::out_of_range("IndexAllocator: Invalid pool index");
        }
        return (ChunkHeader *)(((char*)m_chunks) + (idx * m_chunkSize));
    }

    friend std::ostream& operator << (std::ostream& os, const Pool& pool);

 protected:
    void *m_chunks;
    unsigned m_chunkSize;
    unsigned m_poolIdx;
    unsigned m_poolSize;
};

class IndexAllocatorImpl;
std::ostream& operator << (std::ostream& os, const IndexAllocatorImpl& pool);

// This class is not a template, to save the memory used by code. Remember in
// templates, for each template type, the compiler expands the same code again
// and again. Users should use the template class.
class IndexAllocatorImpl
{
 public:
    enum
    {
        DEFAULT_POOL_SIZE = 1024,
        DEFAULT_MAX_POOLS = 10,
        INVALID_IDX = 0xFFFFFFFF,
        INDEX_ALLOCED = 0x0FFFFFFE,
        GEN_BIT_SHIFT = 29,
        USER_BIT_SHIFT = 26,
        USER_BIT_MASK = (7 << USER_BIT_SHIFT),
        IDX_BIT_MASK = 0x03FFFFFF
    };
    IndexAllocatorImpl(unsigned entrySize,
               unsigned poolSize = DEFAULT_POOL_SIZE,
               unsigned maxPools = DEFAULT_MAX_POOLS,
               bool fixedSize = false);
    ~IndexAllocatorImpl();

    // Return the memory chunk (without the header), but if the memory is not
    // allocated, it throws an exception. To check if the index is allocated
    // use the find() method
    void* operator [](unsigned idx)
    {
        Pool::ChunkHeader* chunk = this->Get(idx);
        if ( (chunk->nextIdx != INDEX_ALLOCED) ||
              GetGen(idx) != GetGen(chunk->idx) )
        {
            throw std::out_of_range("IndexAllocator: Chunk not allocated");
        }
        return chunkToData(chunk);
    }
    
    // If the index is not allocated, it returns NULL, otherwise the allocated
    // memory
    void* find(unsigned idx)
    {
        Pool::ChunkHeader* chunk = this->Get(idx);
        if ( (chunk->nextIdx  != INDEX_ALLOCED) ||
              GetGen(idx) != GetGen(chunk->idx) )
        {
            return NULL;
        }       
        return chunkToData(chunk);
    }
    
    // Gets the chunk pointed to by the index. Not check for allocation is made
    // Used by internal methods
    Pool::ChunkHeader* Get(unsigned idx)
    {
        idx = GetIdx(idx);
        if (idx >= (m_poolSize * m_poolCount))
        {
            throw std::out_of_range("IndexAllocator: Invalid Table Index");
        }
        if (m_pools[idx / m_poolSize] == NULL)
        {
            throw std::out_of_range("IndexAllocator: Pool uninitialized");
        }
        return (*(m_pools[idx / m_poolSize]))[idx % m_poolSize];        
    }

    void* alloc(unsigned *idx = NULL, unsigned userBits = 0);

    void free(void *data);

    const unsigned& size() const
    {
        return m_allocCount;
    }

    static void* chunkToData(Pool::ChunkHeader* cptr)
    {
        return (void*)(((char*)cptr) + sizeof(Pool::ChunkHeader));
    }
    static Pool::ChunkHeader* dataToChunk(void *data)
    {
        return (Pool::ChunkHeader*)(((char*)data) - sizeof(Pool::ChunkHeader));
    }
    
    static unsigned GetUserBits(void *data)
    {
        return ((dataToChunk(data)->idx & USER_BIT_MASK) >> USER_BIT_SHIFT);
    }
    static unsigned GetUserBits(unsigned idx)
    {
        return ((idx & USER_BIT_MASK) >> USER_BIT_SHIFT);
    }    
    static unsigned SetUserBits(unsigned& idx, unsigned bits)
    {
        // Reset and set
        idx = (idx & ~USER_BIT_MASK) | (bits << USER_BIT_SHIFT);
        return idx;
    }    
    static unsigned GetIdx(unsigned idx)
    {
        return (idx & IDX_BIT_MASK);
    }
    static uint8_t GetGen(unsigned idx)
    {
        return (idx >> GEN_BIT_SHIFT);
    }
    static unsigned IncGen(unsigned& idx)
    {
        uint8_t gen = GetGen(idx);
        idx = GetIdx(idx) | (++gen << GEN_BIT_SHIFT);
        return idx;
    }

    friend std::ostream& operator << (std::ostream& os, const IndexAllocatorImpl& pool);
 protected:

    // allocates new pool, or throws on max pools reached
    void allocPool();

    unsigned m_poolSize; // Size of each pools
    unsigned m_maxPools; // Max possible pools
    bool     m_fixedSize; // Flag that specifies if the table is of fixed size 
    unsigned m_chunkSize; // Size of the chunk. Fixed per table.

    Pool **m_pools;
    unsigned m_poolCount;

    unsigned m_allocCount;
    unsigned m_firstFreeIdx;
    unsigned m_lastFreeIdx;
    
    Mutex m_guard;
};

#define ALLOC_DATA_GET_IDX(_data) \
    (eAccelero::IndexAllocatorImpl::dataToChunk((void*)_data)->idx)

template <typename Type> class IndexAllocator;

template <typename Type>
std::ostream& operator << (std::ostream& os, const IndexAllocator<Type>& table)
{
    os << table.m_table;

    return os;
}

/**
 * @class IndexAllocator
 * @file Allocator.h
 * @brief Used for typesafe memory allocation for fixed size data types.
 * Usage:
 *      struct Temp {
 *          int a;
 *          int b;
 *      }
 *      int id;
 *      IndexAllocator<Temp> allocator;
 *      Temp* t = allocator.alloc(&id); // id give a unique number
 *      t->a = 10; t->b = 11;
 *
 *      Temp* tobj = new(t) Temp();
 *  
 *      Temp* t1 = allocator[id];
 *
 *      Temp::~Temp()
 *      allocator.free(t);
 */
template <typename Type>
class IndexAllocator
{
 public:
    /**
     * @brief Creates and initializes the allocator
     * @param [in] poolSize   number of chunks per pool
     * @param [in] maxPools   maximum number of pools
     * @param [in] fixedSize  if false, this allocator can allocate memory until
     *                        system limit. Otherwise the max chunks allocated
     *                        will be maxPools*poolSize
     */
    IndexAllocator(unsigned poolSize = IndexAllocatorImpl::DEFAULT_POOL_SIZE,
                   unsigned maxPools = IndexAllocatorImpl::DEFAULT_MAX_POOLS,
                   bool fixedSize = false)
        : m_table(sizeof(Type), poolSize, maxPools, fixedSize)
    {
    }
    /**
     * @brief Destructor for IndexAllocator
     * @return None
     */
    ~IndexAllocator()
    {
    }
    
    /**
     * @brief Allocates memory location and returns pointer to the Type.
     * @param [out] idx - returns the unique integer. The uniqueness is 
     *      guareented per allocator. If a chunk is freed, the same index
     *      might be reused.
     * @return Allocated pointer to the Type
     * @exception std::bad_alloc when the maximum pools are allocated
     */
    inline Type* alloc(unsigned *idx = NULL)
    {
        return (Type*)m_table.alloc(idx);
    }
    
    /**
     * @brief Frees the memory allocated.
     * @param [in] data - Pointer to the Type, which needs to be returned to the
     *      free pool.
     * @return None
     */    
    inline void free(Type *data)
    {
        m_table.free((void*)data);
    }
    
    /**
     * @brief Given the index, provides the address pointed by the index.
     * @param [in] idx - index for which the memory location is to be fetched
     * @return Returns the memory location pointed to by idx.
     * @exception std::out_of_range if idx is not allocated
     */    
    inline Type* operator[](unsigned idx)
    {
        return reinterpret_cast<Type*>(m_table[idx]);
    }

    inline Type* find(unsigned idx)
    {
        return reinterpret_cast<Type*>(m_table.find(idx));
    }

    /**
     * @brief Returns the number of allocated chunks. 
     * @return Returns the number of allocated chunks
     */        
    inline const unsigned& size() const
    {
        return m_table.size();
    }
    
    friend std::ostream& operator << <>(std::ostream& os, const IndexAllocator& pool);
 protected:
    IndexAllocatorImpl m_table;
};

} // namespace eAccelero

#endif // __EACC_Allocator_h__
