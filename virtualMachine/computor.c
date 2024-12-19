#include "../virtualMachineInterface/computor.h"
#include "../library/include/logger.h"
#include "../library/include/asserts.h"
#include "../library/include/filesystem.h"

static bool boot = false;

bool startComputor()
{
  FORGE_LOG_TRACE("%s is attempting a boot", COMPUTOR_NAME);

  if (boot)
  {
    FORGE_LOG_ERROR("%s is already booted!", COMPUTOR_NAME);
    return false;
  }
  boot              = true;

  FORGE_LOG_TRACE("Allocating RAM of size %lld to %s", PROCESSOR_RAM_SIZE_BYTES, COMPUTOR_NAME);
  computor.ram     = malloc(PROCESSOR_RAM_SIZE_BYTES);
  if (!computor.ram)
  {
    FORGE_LOG_FATAL("Memory allocation failed for %s's RAM. size %lld", COMPUTOR_NAME, PROCESSOR_RAM_SIZE_BYTES);
    return false;
  }
  
  FORGE_LOG_TRACE("Allocating Instruction Memory of size %lld to %s", PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES, COMPUTOR_NAME);
  computor.program = malloc(PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES);
  if (!computor.program)
  {
    FORGE_LOG_FATAL("Memory allocation failed for %s's Instruction Memory. size %lld", COMPUTOR_NAME, PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES);
    return false;
  }

  FORGE_LOG_TRACE("Rewriting %s's Instruction Memory of size %lld", COMPUTOR_NAME, PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES);
  memset(computor.program, 0, PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES);

  FORGE_LOG_INFO("%s successfully booted", COMPUTOR_NAME);
  return true;
}

bool stopComputor()
{
  FORGE_LOG_TRACE("%s is attempting a shutdown", COMPUTOR_NAME);

  if (!boot)
  {
    FORGE_LOG_ERROR("%s is not booted!", COMPUTOR_NAME);
    return false;
  }
  boot              = false;

  FORGE_LOG_TRACE("Freeing %s's RAM", COMPUTOR_NAME);
  if (!computor.ram)
  {
    FORGE_LOG_FATAL("%s has no RAM!", COMPUTOR_NAME);
    return false;
  }
  free(computor.ram);
  
  FORGE_LOG_TRACE("Freeing %s's Instruction Memory", COMPUTOR_NAME);
  if (!computor.program)
  {
    FORGE_LOG_FATAL("%s has no Instruction Memory!", COMPUTOR_NAME);
    return false;
  }
  free(computor.program);

  FORGE_LOG_INFO("%s successfully shutdown", COMPUTOR_NAME);
  return true;
}

bool loadProgram (const char* FILE_PATH)
{
  if (!boot)
  {
    FORGE_LOG_FATAL("%s has not been booted yet. Aborting Program Read");
    return false;
  }

  if (!fileExists(FILE_PATH))
  {
    FORGE_LOG_ERROR("File at  %s does not exist", FILE_PATH);
    return false;
  }

  File file;
  if (!openFile(FILE_PATH, FILE_MODE_READ, true, &file))
  {
    FORGE_LOG_ERROR("%s Could not open the file at %s to read", COMPUTOR_NAME, FILE_PATH);
    return false;
  }

  if (PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES < getFileSize(&file))
  {
    FORGE_LOG_WARNING("The file %s is bigger(%.2f MB) than %s's instruction memory (%.2f MB)", FILE_PATH, getFileSize(&file) / 1024.0f / 1024.0f, COMPUTOR_NAME, PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES / 1024.0f / 1024.0f);
  }

  u64 readSoFar = 0;

  if (!readFile(&file, PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES, computor.program, &readSoFar))
  {
    FORGE_LOG_ERROR("%s failed to read file at %s", COMPUTOR_NAME, FILE_PATH);
    return false;
  }
  closeFile(&file);

  if (readSoFar != PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES)
  {
    FORGE_LOG_WARNING("%s was expecting to read %llu bytes, read only %llu bytes", COMPUTOR_NAME, PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES, readSoFar);
  }

  FORGE_LOG_INFO("%s Instruction Memory rewritten", COMPUTOR_NAME);
  return true;
}

void printInstructionMemory()
{
  if (!boot)
  {
    FORGE_LOG_FATAL("%s has not been booted yet. Aborting Instruction Memory Print");
    return;
  }
  FORGE_ASSERT_MESSAGE(computor.program != NULL, "Cannot print instruction memory if it doesnt exist");

  FORGE_LOG_INFO("\n- - - %s's Instruction Memory (%f MB)- - - \n", COMPUTOR_NAME, PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES / 1024.0f / 1024.0f);

  for (int i = 0; i < PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES; i += 4)
  {
    i8 b0 = computor.program[i];
    i8 b1 = (i + 1 < PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES) ? computor.program[i + 1] : 0;
    i8 b2 = (i + 2 < PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES) ? computor.program[i + 2] : 0;
    i8 b3 = (i + 3 < PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES) ? computor.program[i + 3] : 0;

    FORGE_LOG_DEBUG("(%08d) : %02X %02X %02X %02X", i, b0, b1, b2, b3);
  }
}

void printRAM()
{
  if (!boot)
  {
    FORGE_LOG_FATAL("%s has not been booted yet. Aborting RAM Print");
    return;
  }
  FORGE_ASSERT_MESSAGE(computor.program != NULL, "Cannot print instruction memory if it doesnt exist");

  FORGE_LOG_INFO("\n- - - %s's RAM (%f MB)- - - \n", COMPUTOR_NAME, PROCESSOR_RAM_SIZE_BYTES / 1024.0f / 1024.0f);

  for (int i = 0; i < PROCESSOR_RAM_SIZE_BYTES; i += 4)
  {
    i8 b0 = computor.ram[i];
    i8 b1 = (i + 1 < PROCESSOR_RAM_SIZE_BYTES) ? computor.ram[i + 1] : 0;
    i8 b2 = (i + 2 < PROCESSOR_RAM_SIZE_BYTES) ? computor.ram[i + 2] : 0;
    i8 b3 = (i + 3 < PROCESSOR_RAM_SIZE_BYTES) ? computor.ram[i + 3] : 0;

    FORGE_LOG_DEBUG("(%08d) : %02X %02X %02X %02X", i, b0, b1, b2, b3);
  }
}
