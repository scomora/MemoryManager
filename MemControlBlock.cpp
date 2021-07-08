#include <assert.h>

#include "MemControlBlock.h"
#include "util.h"

MemControlBlock::MemControlBlock()
{
    this->init(0);
}

MemControlBlock::MemControlBlock(size_t size)
{
    this->init(size);
}

void MemControlBlock::init(size_t size)
{
    mSize = size;
    mFree = true;
}

MemControlBlock* MemControlBlock::getBlockFromAddress()
{
    void *controlBlockAddress;
    
    controlBlockAddress = static_cast<void*>(reinterpret_cast<char*>(this) - sizeof(MemControlBlock));

    return static_cast<MemControlBlock*>(controlBlockAddress);
}

MemControlBlock* MemControlBlock::getBlockFromAddress(void* address)
{
    void *controlBlockAddress;
    
    controlBlockAddress = static_cast<void*>(static_cast<char*>(address) - sizeof(MemControlBlock));

    return static_cast<MemControlBlock*>(controlBlockAddress);
}

void* MemControlBlock::getPayloadStartAddress()
{
    void* payloadStart;

    payloadStart = static_cast<void*>(reinterpret_cast<char*>(this) + sizeof(MemControlBlock));

    return payloadStart;
}

void* MemControlBlock::getPayloadEndAddress()
{
    return static_cast<char*>(this->getPayloadStartAddress()) + this->getSize();
}

/**
 * split this memory block into two blocks: one of numBytes bytes
 * and the other of
 * the entire block's size - numBytes - mcb size
 * 
 * return the address of the succeeding block in the split, to
 * be added to the free list
 **/
MemControlBlock* MemControlBlock::split(size_t numBytes)
{
    size_t newPrecedingBlockSize;
    size_t succeedingBlockSize;
    void* succeedingBlockAddress;
    MemControlBlock* succeedingMcb;

    newPrecedingBlockSize = numBytes;
    succeedingBlockSize = this->getSize() - numBytes - sizeof(MemControlBlock);

    this->setSize(newPrecedingBlockSize);

    succeedingBlockAddress = static_cast<char*>(this->getPayloadEndAddress()) + 1;
    succeedingMcb = reinterpret_cast<MemControlBlock*>(succeedingBlockAddress);
    succeedingMcb->init(succeedingBlockSize);

    return succeedingMcb;
}

bool MemControlBlock::isFree()
{
    return mFree;
}

size_t MemControlBlock::getSize()
{
    return mSize;
}

void MemControlBlock::setSize(size_t size)
{
    mSize = size;
}

void MemControlBlock::setFree()
{
    mFree = true;
}

void MemControlBlock::setInUse()
{
    mFree = false;
}