#include "../include/linearAlloc.h"
#include "../include/asserts.h"
#include "../include/logger.h"

void createLinearAllocator(unsigned long long TOTAL_SIZE, void* MEMORY, LinearAllocator* ALLOCATOR) 
{
  FORGE_ASSERT_MESSAGE(ALLOCATOR    != NULL, "Cannot initialize a NULL ALLOACTOR");
  FORGE_ASSERT_MESSAGE(TOTAL_SIZE   >  0,    "Cannot make an ALLOACTOR with non-positive total size");

  ALLOCATOR->totalSize    = TOTAL_SIZE;
  ALLOCATOR->allocated    = 0;
  if (MEMORY != NULL)
  {
    FORGE_LOG_WARNING("Memory is not null");
    ALLOCATOR->ownsMemory = false;
    ALLOCATOR->memory     = MEMORY;
  } 
  else 
  {
    FORGE_LOG_WARNING("The alloactor will own the memory, using malloc");
    ALLOCATOR->ownsMemory = true;
    ALLOCATOR->memory     = malloc(TOTAL_SIZE);
  }
}

void destroyLinearAllocator(LinearAllocator* ALLOCATOR) 
{
  FORGE_ASSERT_MESSAGE(ALLOCATOR    != NULL, "Cannot initialize a NULL ALLOACTOR");

  if (ALLOCATOR->ownsMemory && ALLOCATOR->memory) 
  {
    FORGE_LOG_WARNING("Freeing the allocator memory %p of %lld bytes", ALLOCATOR->memory, ALLOCATOR->allocated);
    free(ALLOCATOR->memory);
  } 
  ALLOCATOR->allocated  = 0;
  ALLOCATOR->memory     = 0;
  ALLOCATOR->totalSize  = 0;
  ALLOCATOR->ownsMemory = false;
}

void* linearAllocatorAllocate(LinearAllocator* ALLOCATOR, unsigned long long SIZE) 
{
  FORGE_ASSERT_MESSAGE(ALLOCATOR    != NULL, "Cannot initialize a NULL ALLOACTOR");
  FORGE_ASSERT_MESSAGE(ALLOCATOR->memory,    "ALLOCATOR has no memory");

  if (ALLOCATOR->allocated + SIZE > ALLOCATOR->totalSize) 
  {
    unsigned long long remaining = ALLOCATOR->totalSize - ALLOCATOR->allocated;
    FORGE_LOG_ERROR("LinearAllocator tried to allocate %lluB, only %lluB remaining.", SIZE, remaining);
    return 0;
  }

  void* block = ((unsigned char*)ALLOCATOR->memory) + ALLOCATOR->allocated;
  ALLOCATOR->allocated += SIZE;
  return block;
}

void linearAllocFree(LinearAllocator* ALLOCATOR) 
{
  FORGE_ASSERT_MESSAGE(ALLOCATOR    != NULL, "Cannot initialize a NULL ALLOACTOR");
  FORGE_ASSERT_MESSAGE(ALLOCATOR->memory,    "ALLOCATOR has no memory");

  ALLOCATOR->allocated = 0;
  memset(ALLOCATOR->memory, 0, ALLOCATOR->totalSize);

  FORGE_LOG_WARNING("ALLOCATOR has freed all the memory");
}
