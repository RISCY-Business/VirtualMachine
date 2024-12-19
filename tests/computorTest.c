#include "../defines.h"
#include "../virtualMachineInterface/computor.h"
#include "../virtualMachineInterface/clock.h"
#include "../library/include/testManager.h"
#include "../library/include/expect.h"
#include <unistd.h>


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
  return true;
}

u8 runComputorFor50UpdatesAndPrintEdges()
{
  static bool prevClock = false;

  for (int i = 0; i < 50; ++i)
  {
    update();

    if (isRisingEdge())
    {
      expectToBeTrue(computor.clock == true && prevClock == false)
    }
    if (isFallingEdge())
    {
      expectToBeTrue(computor.clock == false && prevClock == true);
    }

    prevClock = !prevClock;

    if (i == 32)
    {
      FORGE_LOG_WARNING("This is a visual test, %s should complain about beeing too slow and taking about 5s extra", COMPUTOR_NAME);
      usleep(5 * 1000 * 1000);
    }
  }

  return true;
}

int main() 
{
  registerTest(computorShouldStart, "Starts the computor by creating the ram");
  registerTest(computorShouldNotStart, "Try to start the computor a second time and fail");
  registerTest(runComputorFor50UpdatesAndPrintEdges, "Check if clock is working properly, includes one visual test");
  registerTest(computorShouldNotReadFile, "The file does not exist, the computor should fail to read it");
  registerTest(computorShouldReadFile, "The file does exist its just 0 and 1, read should be successful");
  registerTest(computorShouldStop, "Stop the computor and free the ram");
  registerTest(computorShouldNotStop, "Try to stop the computor a second time and fail");
  registerTest(computorShouldRestart, "Restart and stop the computor");
  runTests();
  return 0;
}
