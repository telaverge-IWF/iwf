#include "Allocator.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace eAccelero;

struct Test
{
    int idx;
    void *ptr;
};

static void printTable(Test **table, int size)
{
    std::cout << "-- Test Table\n";
    for (int i = 0; i < size; i++)
    {
        if (table[i])
            std::cout << "-- " << table[i]->idx << ", " << table[i]->ptr << std::endl;
    }
    std::cout << "-------------\n";
}

int main()
{
    {
        std::cout << "=== Test 1, empty table ===\n";
        IndexAllocator<Test> table(16, 2);

        std::cout << table;
        std::cout << "===========================\n";
    }

    {
        std::cout << "=== Test 2, 32 allocs ===\n";
        IndexAllocator<Test> table(16, 2);
        unsigned idx;
        Test *checkTable[32] = {NULL};
        for (int i = 0; i < 32; i++)
        {
            Test* ptr= table.alloc(&idx);
            ptr->idx = idx;
            ptr->ptr = ptr;
            checkTable[i] = ptr;
        }
        printTable(checkTable, 32);
        std::cout << table;
        std::cout << "===========================\n";
    }

    {
        std::cout << "=== Test 3, 32 allocs/free ===\n";
        IndexAllocator<Test> table(16, 2);
        unsigned idx;
        Test *checkTable[32] = {NULL};
        for (int i = 0; i < 32; i++)
        {
            Test* ptr= table.alloc(&idx);
            ptr->idx = idx;
            ptr->ptr = ptr;
            checkTable[i] = ptr;
        }
        for (int i = 31; i >= 0; i--)
        {
            table.free(checkTable[i]);
            checkTable[i] = NULL;
        }

        printTable(checkTable, 32);
        std::cout << table;
        std::cout << "===========================\n";
    }

    {
        std::cout << "=== Test 4, 32 allocs/random free ===\n";
        IndexAllocator<Test> table(16, 2);
        unsigned idx;
        unsigned delIdx = 0;
        Test *checkTable[32] = {NULL};
        int count = 0;
        srandom(time(NULL));
        for (int i = 0; i < 32; i++)
        {
            Test* ptr= table.alloc(&idx);
            ptr->idx = idx;
            ptr->ptr = ptr;
            checkTable[i] = ptr;
            count++;

            delIdx = random() % (count+1);
            if (delIdx)
            {
                delIdx--;
                if (checkTable[delIdx])
                {
                    std::cout << "## Deleting index " << delIdx << std::endl;
                    table.free(checkTable[delIdx]);
                    checkTable[delIdx] = NULL;
                }
            }
        }

        printTable(checkTable, 32);
        std::cout << table;
        std::cout << "===========================\n";
    }

    return 0;
}

