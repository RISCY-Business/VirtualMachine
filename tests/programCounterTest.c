#include "allTests.h"
#include "../library/include/logger.h"

u8 checkProgramCounter0AtStart()
{
  expectShouldBe(0, getProgramCounter());
  return true;
}

u8 checkUpdateProgramCounter()
{
  setProgramCounter(0);
  for (int i = 0; i < 5; ++i)
  {
    if (!isRisingEdge()) continue;
    expectShouldBe(i * 4, getProgramCounter());
    expectShouldBe(i + 2, getInstruction());
    update();
  }
  return true;
}

u8 checkSetProgramCounter()
{
  for (int i = 0; i < 5; ++i)
  {
    if (!isRisingEdge()) continue;
    expectToBeTrue(setProgramCounter(i * i * 4));
    expectShouldBe(i * i * 4, getProgramCounter());
    update();
  }
  return true;
}

u8 checkSetProgramCounterFail()
{
  FORGE_LOG_WARNING("This test will generate an error");
  expectToBeFalse(setProgramCounter(PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES + 4));
  return true;
}

u8 checkInstructions()
{
  FORGE_LOG_WARNING("This function assumes that the instruction memory is already to 1 -> 2 -> 3 -> 4 -> 5..");
  for (int i = 0; i < 5; ++i)
  {
    FORGE_LOG_DEBUG("(%08d) : %d", convertRegisterIndexToAddress(i), computor.memRam.registers[i].value);
  }
  expectShouldBe(0, getProgramCounter());

  setProgramCounter(0);
  for (int i = 0; i < 5; ++i)
  {
    if (!isRisingEdge()) continue;
    FORGE_LOG_TRACE("Memory : %d", computor.memRam.registers[convertAddressToRegisterIndex(getProgramCounter())].value);
    expectShouldBe(i + 1, getInstruction());
    update();
  }
  return true;
}
