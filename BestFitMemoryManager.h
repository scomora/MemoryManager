#ifndef BESTFITMEMORYMANAGER
#define BESTFITMEMORYMANAGER

#include "MemoryManager.h"

class BestFitMemoryManager : public MemoryManager
{
    public:
        BestFitMemoryManager(size_t wordSize = sizeof(int));
        ~BestFitMemoryManager();
        virtual void* alloc(size_t sizeInBytes);
        virtual void free(void* address);
};

#endif /* BESTFITMEMORYMANAGER */
