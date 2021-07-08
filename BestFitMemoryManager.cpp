
#include "BestFitMemoryManager.h"

#include <iostream>

BestFitMemoryManager::BestFitMemoryManager()
:   MemoryManager()
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
    size_t originalSize {sizeInBytes};

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
            freeBlockFromSplit = currBestFit->split(sizeInBytes);
            this->mFreeList.push_back(freeBlockFromSplit);
        }
        
        this->mFreeList.remove(currBestFit);
        return currBestFit->getPayloadStartAddress();
    }

    return 0;
}