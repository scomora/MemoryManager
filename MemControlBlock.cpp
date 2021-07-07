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

bool MemControlBlock::isFree()
{
    return mFree;
}

size_t MemControlBlock::getSize()
{
    return mSize;
}

void MemControlBlock::setFree()
{
    mFree = true;
}

void MemControlBlock::setInUse()
{
    mFree = false;
}