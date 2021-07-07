
#include "MemControlBlock.h"
#include "MemoryManager.h"
#include <unistd.h>

MemoryManager::MemoryManager(size_t wordSize, allocator_t& allocator)
    :   mWordSize(wordSize),
        mAllocator(allocator)
{
    MemControlBlock* mcb;

    this->initialize(INITIAL_HEAP_SIZE_BYTES);
    mcb = static_cast<MemControlBlock*>(mMemStart);
    mcb->init(INITIAL_HEAP_USER_SIZE_BYTES);
    mFreeList.push_front(mcb);
}

MemoryManager::allocator_t MemoryManager::sWorstFit = 
    [](ssize_t numBytes, std::list<MemControlBlock*>& freeList) -> ssize_t 
    {
        UNUSED_VAR(numBytes);
        UNUSED_VAR(freeList);
        return 0;
    };

MemoryManager::allocator_t MemoryManager::sBestFit = 
    [](ssize_t numBytes, std::list<MemControlBlock*>& freeList) -> ssize_t 
    {
        UNUSED_VAR(numBytes);
        UNUSED_VAR(freeList);
        return 0;
    };

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

void* MemoryManager::alloc(size_t sizeInBytes)
{
    return reinterpret_cast<void*>(this->mAllocator(static_cast<ssize_t>(sizeInBytes), mFreeList));
}

void MemoryManager::free(void* address)
{
    UNUSED_VAR(address);
}

void MemoryManager::setAllocator(allocator_t allocator)
{
    UNUSED_VAR(allocator);
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