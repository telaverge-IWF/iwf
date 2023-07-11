#include "MemPool.h"
#include <iostream>

using namespace eAccelero;

static MemPool pool;

void CheckMem(void *ptr, unsigned bi, unsigned id)
{
    std::cout << "---------- Validating Mem ------------\n";
    unsigned idx = IndexAllocatorImpl::dataToChunk(ptr)->idx;
    unsigned bin = IndexAllocatorImpl::GetUserBits(idx);
    unsigned i = (idx & IndexAllocatorImpl::IDX_BIT_MASK);
    std::cout << "Bin: " << bin
              << " Idx: " << i 
              << " Ptr: " << ptr
              << " " << pool[idx]
              << std::endl;
    EACC_ASSERT((bi == bin && idx == id));
    std::cout << "---------------------------------------\n";
}

int main()
{
  
    {
        unsigned idx;
        void *ptr = pool.Alloc(100, &idx);
        CheckMem(ptr, 1, idx);
        EACC_ASSERT(pool[idx] == ptr);
        
        void *ptr1 = pool.Alloc(80, &idx);
        CheckMem(ptr1, 1, idx);
        EACC_ASSERT(pool[idx] == ptr1);

        pool.Free(ptr);
        pool.Free(ptr1);
        
        ptr = pool.Alloc(72, &idx);
        CheckMem(ptr, 1, idx);
        EACC_ASSERT(pool[idx] == ptr);
        
        pool.Free(ptr);
    }
    {
        unsigned idx;
        void *ptr = pool.Alloc(64, &idx);
        CheckMem(ptr, 0, idx);
        EACC_ASSERT(pool[idx] == ptr);
        pool.Free(ptr);
    }
    {
        unsigned idx;
        void *ptr = pool.Alloc(257, &idx);
        CheckMem(ptr, 3, idx);
        EACC_ASSERT(pool[idx] == ptr);
        pool.Free(ptr);
    }
    {
        unsigned idx;
        void *ptr = pool.Alloc(8000, &idx);
        CheckMem(ptr, 6, idx);
        EACC_ASSERT(pool[idx] == ptr);
        pool.Free(ptr);
    }
    
    std::cout << "Pool count = " << pool.count() << std::endl;
    EACC_ASSERT(pool.count() == 0)
    
    return 0;
}
