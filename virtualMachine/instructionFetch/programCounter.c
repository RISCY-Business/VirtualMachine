#include "../../virtualMachineInterface/include.h"
#include "../../library/include/logger.h"


void  updateProgramCounter()
{
  if (!isRisingEdge()) return;

  if (computor.programCounter.busValue != computor.programCounter.value)
  {
    FORGE_LOG_TRACE("Setting program counter to %d from %d", computor.programCounter.busValue, computor.programCounter.value);
    computor.programCounter.value = computor.programCounter.busValue;
    return;
  }

  computor.programCounter.value     += 4;
  computor.programCounter.busValue  += 4;
}

bool setProgramCounter(u32 ADDRESS)
{
  if (convertAddressToRegisterIndex(ADDRESS) == -1)
  {
    FORGE_LOG_ERROR("This address exceeds %s's Instruction Memory size of %d", COMPUTOR_NAME, PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES);
    return false;
  }

  if (ADDRESS % 4 != 0)
  {
    FORGE_LOG_ERROR("Program counter is allowed to jump only to numbers that are multiples of 4, since a register is 4 bytes");
    return false;
  }

  computor.programCounter.busValue  = ADDRESS;
  if (isRisingEdge())
  {
    computor.programCounter.value   = ADDRESS;
  }
  return true;
}

u32 getProgramCounter()
{
  return computor.programCounter.value;
}

u32 getInstruction()
{
  return readMemoryRam(getProgramCounter());
}
