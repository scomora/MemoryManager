
#include "BestFitMemoryManager.h"
#include "MemoryManager.h"
#include "MemControlBlock.h"

#include <iostream>
#include <vector>

bool testMemControlBlock();
void testRealloc();

int main(int argc, char** argv)
{
    UNUSED_VAR(argc);
    UNUSED_VAR(argv);

    testRealloc();

    testMemControlBlock();

    return 0;
}

void testRealloc()
{
    BestFitMemoryManager mm;
    char* byteArray;
    constexpr size_t smallerSize = 8;
    constexpr size_t biggerSize = 20;
    size_t fillIdx;
    char* biggerByteArray;

    byteArray = reinterpret_cast<char*>(mm.alloc(smallerSize));

    for (fillIdx = 0; fillIdx < smallerSize; fillIdx++)
    {
        byteArray[fillIdx] = static_cast<char>(fillIdx + 1);
    }

    biggerByteArray = reinterpret_cast<char*>(mm.realloc(byteArray, biggerSize));
}

bool testMemControlBlock()
{
    BestFitMemoryManager bfmm;
    void* heapMem;
    MemControlBlock* mcb;
    size_t numAllocs {0};
    void* heapAddresses[8192 * sizeof(void*)];
    size_t putIdx{0};
    size_t getIdx{0};

    int* num = reinterpret_cast<int*>(bfmm.alloc(sizeof(*num)));
    *num = 0x3744;
    std::cout << "alloced " << reinterpret_cast<void*>(*num) << std::endl;
    bfmm.free(num);

    for (; ; numAllocs++)
    {
        heapMem = reinterpret_cast<MemControlBlock*>(bfmm.alloc(8));

        if (heapMem == nullptr)
        {
            bfmm.free(heapAddresses[getIdx++]);
            continue;
        }

        std::memset(heapMem, 0x37, 8);

        heapAddresses[putIdx++] = heapMem;
    }
    
    std::cout << "got " << numAllocs << " allocs before running out of mem" << std::endl;
    return false;
}