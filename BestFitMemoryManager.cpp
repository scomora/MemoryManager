
#include "BestFitMemoryManager.h"

#include <iostream>
#include <limits>

BestFitMemoryManager::BestFitMemoryManager(size_t wordSize)
:   MemoryManager(wordSize)
{

}

BestFitMemoryManager::~BestFitMemoryManager()
{

}

void* BestFitMemoryManager::alloc(size_t sizeInBytes)
{
    ssize_t currSmallestDiff{std::numeric_limits<ssize_t>::max()};
    MemControlBlock* currBestFit {nullptr};
    MemControlBlock* freeBlockFromSplit {nullptr};
    ssize_t thisDiff;

    if (!sizeInBytes)
    {
        return nullptr;
    }

    if (this->getState() == MemoryManager::State::OUT_OF_MEM)
    {
        return nullptr;
    }

    this->setMostRecentRequestSize(sizeInBytes);

    sizeInBytes += sizeof(MemControlBlock);
    sizeInBytes = this->alignBytes(sizeInBytes);

    for (MemControlBlock*& mcb : this->mFreeList)
    {
        thisDiff = static_cast<size_t>(mcb->getSize() + sizeof(MemControlBlock) - sizeInBytes);
        if (thisDiff >= 0 && thisDiff < currSmallestDiff)
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
        if (currBestFit->getSize() >= (sizeof(MemControlBlock) + sizeInBytes))
        {
            freeBlockFromSplit = currBestFit->split(sizeInBytes, this->getWordSize());
            this->mFreeList.push_front(freeBlockFromSplit);
        }
        else
        {
            int x{0};
            x++;
        }
        
        this->mFreeList.remove(currBestFit);
        return currBestFit->getPayloadStartAddress();
    }

    /* get more memory */
    this->handleOutOfMemory(sizeInBytes);

    if (this->getState() == MemoryManager::State::OUT_OF_MEM)
    {
        return nullptr;
    }

    /* then try again */
    return this->alloc(this->getMostRecentRequestSize());
}

void BestFitMemoryManager::free(void* address)
{
    MemControlBlock* blockToFree {MemControlBlock::getBlockFromAddress(address)};

    if (blockToFree == nullptr)
    {
        std::cout << "failed to free block (user address = " << address << "; mcb = " << reinterpret_cast<void*>(blockToFree) << std::endl;
    }

    blockToFree->setFree();
    this->mFreeList.push_back(blockToFree);
}