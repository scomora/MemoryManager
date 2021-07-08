
#include "BestFitMemoryManager.h"
#include "MemoryManager.h"
#include "MemControlBlock.h"

#include <iostream>

bool testMemControlBlock();

#define STR(x)  #x

template<typename T>
static constexpr void print_size(T varSize)
{
    std::cout << "sizeof(" << STR(T) << ") = " << sizeof(T) << std::endl;
}

int main(int argc, char** argv)
{
    UNUSED_VAR(argc);
    UNUSED_VAR(argv);

    std::cout << "sizeof(int) = " << sizeof(int) << std::endl;
    std::cout << "sizeof(void*) = " << sizeof(void*) << std::endl;

    testMemControlBlock();

    return 0;
}

constexpr size_t PAYLOAD_SIZE = 4 * 1024;

bool testMemControlBlock()
{
    BestFitMemoryManager bfmm(PAYLOAD_SIZE);
    void* heapMem;
    MemControlBlock* mcb;
    size_t numAllocs {0};

    heapMem = bfmm.alloc(4);

    for (; ; numAllocs++)
    {
        heapMem = reinterpret_cast<MemControlBlock*>(bfmm.alloc(PAYLOAD_SIZE));

        if (heapMem == nullptr)
        {
            break;
        }

        std::memset(heapMem, 0x37, PAYLOAD_SIZE);

        mcb->init(sizeof(MemControlBlock));
        // std::cout << "got " << reinterpret_cast<void*>(mcb) << std::endl;
    }
    
    std::cout << "got " << numAllocs << " allocs before running out of mem" << std::endl;
    return false;
}