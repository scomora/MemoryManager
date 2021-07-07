#ifndef BESTFITMEMORYMANAGER
#define BESTFITMEMORYMANAGER

#include "MemoryManager.h"

class BestFitMemoryManager : public MemoryManager
{
    public:
        BestFitMemoryManager();
        ~BestFitMemoryManager();
        virtual void* alloc(size_t sizeInBytes);
};

#endif /* BESTFITMEMORYMANAGER */
