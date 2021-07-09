#ifndef MEMORYMANAGER
#define MEMORYMANAGER

#include <bitset>
#include <cstddef>
#include <functional>
#include <list>
#include <memory>
#include <string>

#include "Logger.h"
#include "MemControlBlock.h"
#include "util.h"

class MemoryManager
{
    public:
        enum class State
        {
            HEALTHY = 0,
            OUT_OF_MEM
        };

        MemoryManager(size_t wordSize = sizeof(void*));
        ~MemoryManager();
        void initialize(size_t sizeInWords);
        void shutdown();
        virtual void* alloc(size_t sizeInBytes) = 0;
        virtual void free(void* address) = 0;
        void* realloc(void* address, size_t numBytes);
        int dumpMemoryMap(const std::string &fileName);
        void* getList();
        void* getBitMap();
        size_t getWordSize();
        void* getMemoryStart();
        size_t getMemoryLimit();
        State getState();
        void setState(State nextState);

    protected:
        State mState;
        
        size_t alignBytes(size_t numBytes);
        void handleOutOfMemory(size_t bytesNeeded);
        std::list<MemControlBlock*> mFreeList;
        size_t getMostRecentRequestSize();
        void setMostRecentRequestSize(size_t mostRecentRequestSize);
        void log(std::string& message);

    private:
        void* mMemStart;
        size_t mWordSize;
        size_t mMostRecentRequestSize;
        Logger mLogger;

        static constexpr size_t INITIAL_HEAP_USER_SIZE_BYTES    = 32;
        static constexpr size_t INITIAL_HEAP_SIZE_BYTES         = INITIAL_HEAP_USER_SIZE_BYTES 
                                                                  + sizeof(MemControlBlock);

};

#endif /* MEMORYMANAGER */
