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
        MemControlBlock* split(size_t numBytes, size_t alignment);
        void* getPayloadStartAddress();
        void* getPayloadEndAddress();
        static MemControlBlock* getBlockFromAddress(void* address);
        size_t getSize();
        void setSize(size_t size);
        void setFree();
        void setInUse();
        bool isFree();
        static constexpr size_t GET_SIZE();
        static size_t roundUp(size_t num, size_t multiple);

    private:
        size_t mSize;
        bool mFree;
};

#endif /* MEMCONTROLBLOCK */
