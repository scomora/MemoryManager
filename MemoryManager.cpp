
#include "MemControlBlock.h"
#include "MemoryManager.h"
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

#if 0
MemoryManager::allocator_t MemoryManager::sWorstFit = 
    [](ssize_t numBytes, std::list<MemControlBlock*>& freeList) -> ssize_t 
    {
        ssize_t currSmallestDiff {numBytes};
        MemControlBlock* currBestFit {nullptr};
        ssize_t thisDiff;

        // numBytes = 

        for (MemControlBlock*& mcb : freeList)
        {
            thisDiff = mcb->getSize() - numBytes;
            // if (thisDiff > )
        }
        return 0;
    };
#endif

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