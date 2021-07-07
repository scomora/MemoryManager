#include "MemoryManager.h"
#include "MemControlBlock.h"

#include <iostream>

bool testMemControlBlock();

int main(int argc, char** argv)
{
    UNUSED_VAR(argc);
    UNUSED_VAR(argv);

    testMemControlBlock();

    return 0;
}

constexpr size_t PAYLOAD_SIZE = sizeof(MemControlBlock) << 1;

bool testMemControlBlock()
{
    MemControlBlock *mcb;
    void *blockAddress;

    void *payload = new char[PAYLOAD_SIZE];
    mcb = static_cast<MemControlBlock*>(payload);

    std::memset(payload, 0, PAYLOAD_SIZE);
    mcb->setFree();
    blockAddress = mcb->getBlockFromAddress();

    std::cout << "sizeof(mcb) = " << sizeof(MemControlBlock) << std::endl;

    std::cout << "MCB address: " << static_cast<void*>(mcb) << std::endl;
    std::cout << "Block address: " << blockAddress << std::endl;

    return false;
}