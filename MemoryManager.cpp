
#include "MemControlBlock.h"
#include "MemoryManager.h"

#include <memory>
#include <unistd.h>

MemoryManager::MemoryManager(size_t wordSize)
    :   mWordSize(wordSize)
{
    MemControlBlock* mcb;

    this->initialize(INITIAL_HEAP_SIZE_BYTES);
    mcb = static_cast<MemControlBlock*>(mMemStart);
    mcb->init(INITIAL_HEAP_USER_SIZE_BYTES);
    mFreeList.push_front(mcb);
}

MemoryManager::~MemoryManager()
{

}

void MemoryManager::initialize(size_t sizeInWords)
{
    mMemStart = sbrk(sizeInWords);
}

void MemoryManager::shutdown()
{

}

void MemoryManager::free(void* address)
{
    UNUSED_VAR(address);
}

int MemoryManager::dumpMemoryMap(const std::string &fileName)
{
    UNUSED_VAR(fileName);
    return 0;
}

void* MemoryManager::getList()
{
    return nullptr;
}

void* MemoryManager::getBitMap()
{
    return nullptr;
}

size_t MemoryManager::getWordSize()
{
    return 0;
}

void* MemoryManager::getMemoryStart()
{
    return nullptr;
}

size_t MemoryManager::getMemoryLimit()
{
    return 0;
}

size_t MemoryManager::alignBytes(size_t numBytes)
{
    return ((numBytes + this->mWordSize - 1) & ~(this->mWordSize - 1));
}