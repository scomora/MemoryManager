#ifndef MEMCONTROLBLOCK
#define MEMCONTROLBLOCK

#include "types.h"

class MemControlBlock
{
    public:
        MemControlBlock();
        MemControlBlock(size_t size);
        void init(size_t size);
        MemControlBlock* getBlockFromAddress();
        void* getPayloadStartAddress();
        static MemControlBlock* getBlockFromAddress(void* address);
        size_t getSize();
        void setSize(size_t size);
        void setFree();
        void setInUse();
        bool isFree();

    private:
        size_t mSize;
        bool mFree;
};

#endif /* MEMCONTROLBLOCK */
