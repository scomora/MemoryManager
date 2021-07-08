
#include "BestFitMemoryManager.h"
#include "MemoryManager.h"
#include "MemControlBlock.h"

#include <iostream>

bool testMemControlBlock();

int main(int argc, char** argv)
{
    UNUSED_VAR(argc);
    UNUSED_VAR(argv);

    testMemControlBlock();
    BestFitMemoryManager bestFit;

    return 0;
}

constexpr size_t PAYLOAD_SIZE = sizeof(MemControlBlock) << 1;

bool testMemControlBlock()
{
    BestFitMemoryManager bfmm;
    void* heapMem;
    MemControlBlock* mcb;
    size_t numAllocs {0};

    heapMem = bfmm.alloc(4);

    for (; numAllocs < 1363; numAllocs++)
    {
        mcb = reinterpret_cast<MemControlBlock*>(bfmm.alloc(sizeof(MemControlBlock)));
        mcb->init(sizeof(MemControlBlock));
        std::cout << "got " << reinterpret_cast<void*>(mcb) << std::endl;
    }
    

    return false;
}