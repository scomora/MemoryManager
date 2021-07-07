
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
    ssize_t thisDiff;
    size_t originalSize {sizeInBytes};

    sizeInBytes += sizeof(MemControlBlock);
    sizeInBytes = this->alignBytes(sizeInBytes);

    std::cout << "requested " << originalSize << " ; requesting " << sizeInBytes << std::endl;

    for (MemControlBlock*& mcb : this->mFreeList)
    {
        thisDiff = static_cast<size_t>(mcb->getSize() - sizeInBytes);
        if (thisDiff < currSmallestDiff)
        {
            std::cout << "probing free block with diff " << thisDiff << std::endl;
            currSmallestDiff = thisDiff;
            currBestFit = mcb;
        }
    }

    if (currBestFit)
    {
        currBestFit->setSize(sizeInBytes);
        currBestFit->setInUse();
        return currBestFit->getPayloadStartAddress();
    }

    return 0;
}