
#include "BestFitMemoryManager.h"

#include <iostream>

BestFitMemoryManager::BestFitMemoryManager(size_t wordSize)
:   MemoryManager(wordSize)
{

}

BestFitMemoryManager::~BestFitMemoryManager()
{

}

void* BestFitMemoryManager::alloc(size_t sizeInBytes)
{
    ssize_t currSmallestDiff;
    MemControlBlock* currBestFit {nullptr};
    MemControlBlock* freeBlockFromSplit {nullptr};
    ssize_t thisDiff;
    this->setMostRecentRequestSize(sizeInBytes);

    sizeInBytes += sizeof(MemControlBlock);
    sizeInBytes = this->alignBytes(sizeInBytes);

    for (MemControlBlock*& mcb : this->mFreeList)
    {
        thisDiff = static_cast<size_t>(mcb->getSize() - sizeInBytes);
        if (thisDiff > 0 && thisDiff < currSmallestDiff)
        {
            currSmallestDiff = thisDiff;
            currBestFit = mcb;
        }
    }

    if (currBestFit)
    {
        currBestFit->setInUse();

        /* if the size of the block, after accounting for the minimum size,
           is at least the word size, split it into two blocks */
        if (currBestFit->getSize() - sizeInBytes >= this->getWordSize())
        {
            freeBlockFromSplit = currBestFit->split(sizeInBytes, this->getWordSize());
            this->mFreeList.push_front(freeBlockFromSplit);
        }
        
        this->mFreeList.remove(currBestFit);
        return currBestFit->getPayloadStartAddress();
    }

    /* get more memory */
    this->handleOutOfMemory();

    if (this->getState() == MemoryManager::State::OUT_OF_MEM)
    {
        return nullptr;
    }

    /* then try again */
    return this->alloc(this->getMostRecentRequestSize());
}