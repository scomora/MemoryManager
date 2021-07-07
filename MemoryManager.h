#ifndef MEMORYMANAGER
#define MEMORYMANAGER

#include <bitset>
#include <cstddef>
#include <functional>
#include <list>
#include <memory>
#include <string>

#include "MemControlBlock.h"
#include "util.h"

class MemoryManager
{
    public:
        using allocator_t = std::function<ssize_t(ssize_t, std::list<MemControlBlock*>&)>;
        MemoryManager(size_t wordSize, allocator_t& allocator);
        ~MemoryManager();
        void initialize(size_t sizeInWords);
        void shutdown();
        void* alloc(size_t sizeInBytes);
        void free(void* address);
        void setAllocator(allocator_t allocator);
        int dumpMemoryMap(const std::string &fileName);
        void* getList();
        void* getBitMap();
        size_t getWordSize();
        void* getMemoryStart();
        size_t getMemoryLimit();

    private:
        void* mMemStart;
        size_t mWordSize;
        allocator_t& mAllocator;
        static allocator_t sBestFit;
        static allocator_t sWorstFit;
        std::list<MemControlBlock*> mFreeList;

        static constexpr size_t INITIAL_HEAP_USER_SIZE_BYTES    = 65536UL;
        static constexpr size_t INITIAL_HEAP_SIZE_BYTES         = INITIAL_HEAP_USER_SIZE_BYTES 
                                                                  + sizeof(MemControlBlock);

};

#endif /* MEMORYMANAGER */
