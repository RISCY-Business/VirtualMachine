#include "allTests.h"

u8 computorShouldStart()
{
  expectToBeTrue(startComputor());
  return true;
}

u8 computorShouldNotStart()
{
  FORGE_LOG_WARNING("This test will cause an error");
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
  FORGE_LOG_WARNING("This test will cause an error");
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
  FORGE_LOG_WARNING("This test will cause an error");
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
      FORGE_LOG_WARNING("This is a visual test, %s should complain about beeing too slow and taking about 1s extra", COMPUTOR_NAME);
      usleep(1 * 1000 * 1000);
    }
  }

  return true;
}

