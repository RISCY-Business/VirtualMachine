#include "../virtualMachineInterface/computor.h"
#include "../virtualMachineInterface/clock.h"
#include "../library/include/logger.h"
#include "../virtualMachineInterface/registers.h"
#include "../library/include/asserts.h"
#include "../library/include/filesystem.h"

static bool boot = false;

// - - - start computor
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


  FORGE_LOG_TRACE("Resetting all registers of %s, count : %d", COMPUTOR_NAME, registerCount);
  for (int i = 0; i < registerCount; ++i)
  {
    computor.registers[i].value = 0;
  }

  FORGE_LOG_TRACE("Running %s's clock at %lld hz", COMPUTOR_NAME, CLOCK_FREQUENCY_HERTZ);
  computor.clock = false;

  FORGE_LOG_INFO("%s successfully booted", COMPUTOR_NAME);
  return true;
}

// - - - stop computor
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

// - - - load program
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
  if (!openFile(FILE_PATH, FILE_MODE_READ, false, &file))
  {
    FORGE_LOG_ERROR("%s Could not open the file at %s to read", COMPUTOR_NAME, FILE_PATH);
    return false;
  }

  if (PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES < getFileSize(&file))
  {
    FORGE_LOG_WARNING("The file %s is bigger(%.2f KB) than %s's instruction memory (%.2f KB)", FILE_PATH, getFileSize(&file) / 1024.0f, COMPUTOR_NAME, PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES / 1024.0f);
  }

  memset(computor.program, 0, PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES);

  char*     lineRead;
  int       lineNumber = 0;

  while (lineNumber * 4 < PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES && readFileLine(&file, &lineRead))
  {
    if (strlen(lineRead) != 32 + 1) // - - - +! for null character 
    {
      FORGE_LOG_WARNING("Line %d in %s has invalid length (%zu characters). Expected exactly 32 characters.", 
                              lineNumber, FILE_PATH, strlen(lineRead));
      free(lineRead);
      continue;    
    }
    u32 instruction = 0;

    for (int i = 0; i < 32; ++i)
    {
      if (lineRead[i] == '1')
      {
        instruction |= (1 << (31 - i));
      }
      else if (lineRead[i] != '0')
      {
        FORGE_LOG_WARNING("Invalid character '%c' at line %d, position %d.\nSkipping : %s", lineRead[i], lineNumber, i, lineRead);
        instruction = 0;
        break;
      }
    }

    // - - - store the instruction in program memory 
    computor.program[lineNumber * 4 + 0] = (instruction >> 24) & 0xFF;
    computor.program[lineNumber * 4 + 1] = (instruction >> 16) & 0xFF;
    computor.program[lineNumber * 4 + 2] = (instruction >> 8) & 0xFF;
    computor.program[lineNumber * 4 + 3] = instruction & 0xFF;

    lineNumber++;
    free (lineRead);
  }

  closeFile(&file);

  if (lineNumber * 4 != PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES)
  {
    FORGE_LOG_WARNING("%s was expecting to read %llu bytes, read only %llu bytes", COMPUTOR_NAME, PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES, lineNumber * 4);
  }

  FORGE_LOG_INFO("%s Instruction Memory rewritten", COMPUTOR_NAME);
  return true;
}

// - - - print instruction memory
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

    FORGE_LOG_DEBUG("(%08d) : %d %d %d %d", i, b0, b1, b2, b3);
  }
}

// - - - print ram
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

    FORGE_LOG_DEBUG("(%08d) : %d %d %d %d", i, b0, b1, b2, b3);
  }
}

// - - - print registers 
void printRegisters()
{
  FORGE_LOG_INFO("- - - %d Registers of %s - - -", registerCount, COMPUTOR_NAME);
  for (int i = 0; i < registerCount; ++i)
  {
    printRegisterValue(i);
  }
}

// - - - update
void update()
{
  // - - - update clock first
  updateClock();

  // - - - update the registers 
  updateRegisters();
}
