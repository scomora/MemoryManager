
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

    heapMem = bfmm.alloc(4);

    std::cout << "got heap mem = " << heapMem << std::endl;
    std::cout << "malloc(10) gives " << malloc(10) << std::endl;

    return false;
}