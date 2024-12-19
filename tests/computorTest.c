#include "../defines.h"
#include "../virtualMachineInterface/computor.h"
#include "../library/include/testManager.h"
#include "../library/include/expect.h"


u8 computorShouldStart()
{
  expectToBeTrue(startComputor());
  return true;
}

u8 computorShouldNotStart()
{
  expectToBeFalse(startComputor());
  return true;
}

u8 computorShouldStop()
{
  expectToBeTrue(stopComputor());
  return true;
}

u8 computorShouldNotStop()
{
  expectToBeFalse(stopComputor());
  return true;
}

u8 computorShouldRestart()
{
  expectToBeTrue(startComputor());
  expectToBeTrue(stopComputor());
  return true;
}

u8 computorShouldReadFile()
{
  expectToBeTrue(loadProgram("program.txt"));
  printInstructionMemory();
  return true;
}

u8 computorShouldNotReadFile()
{
  expectToBeFalse(loadProgram("notProgram.txt"));
  printInstructionMemory();
  printRAM();
  return true;
}

int main() 
{
  registerTest(computorShouldStart, "Starts the computor by creating the ram");
  registerTest(computorShouldNotStart, "Try to start the computor a second time and fail");
  registerTest(computorShouldNotReadFile, "The file does not exist, the computor should fail to read it");
  registerTest(computorShouldReadFile, "The file does exist its just 0 and 1, read should be successful");
  registerTest(computorShouldStop, "Stop the computor and free the ram");
  registerTest(computorShouldNotStop, "Try to stop the computor a second time and fail");
  registerTest(computorShouldRestart, "Restart and stop the computor");
  runTests();
  return 0;
}
