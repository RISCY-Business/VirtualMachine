#include "allTests.h"

u8 successfullyPrintAllRegisterNames()
{
  for (int i = 0; i < registerCount; ++i)
  {
    const char* name = getRegisterName(i);
    expectShouldNotBe(NULL, name);

    FORGE_LOG_DEBUG("%s", name);
  }
  return true;
}

u8 successfullyFailAtGettingRegisterName()
{
  FORGE_LOG_WARNING("This test will contain an error");
  if (NULL != getRegisterName(registerCount))
  {
    return false;
  }
  if (NULL != getRegisterName(123))
  {
    return false;
  }

  return true;
}

u8 checkAllRegistersZero()
{
  for (int i = 0; i < registerCount; ++i)
  {
    expectShouldBe(0, readRegister(i));
  }
  return true;
}

u8 writeAllRegisters()
{
  while (!isRisingEdge())
  {
    update();
  }
  
  expectToBeTrue(isRisingEdge());

  for (int i = 1; i < registerCount; ++i)
  {
    expectToBeTrue(writeRegister(i, i));
  }

  update();
  while (!isRisingEdge())
  {
    update();
  }

  expectToBeTrue(isRisingEdge());

  for (int i = 0; i < registerCount; ++i)
  {
    printRegisterValue(i);
    expectShouldBe(i, readRegister(i));
  }
  return true;
}

u8 writeAllRegistersAtLowEdge()
{
  FORGE_LOG_WARNING("This test will cause an error");
  while (isRisingEdge())
  {
    update();
  }

  for (int i = 1; i < registerCount; ++i)
  {
    expectToBeTrue(writeRegister(i, i + 1));
  }

  while (!isRisingEdge())
  {
    update();
  }

  for (int i = 1; i < registerCount; ++i)
  {
    expectShouldBe(i + 1, readRegister(i));
  }
  return true;
}

u8 failAtWriteAtZero()
{
  FORGE_LOG_WARNING("This test will cause an error");
  while (!isRisingEdge())
  {
    update();
  }

  expectToBeFalse(writeRegister(zero, rand()));
  return true;
}

u8 successfullyPrintAllRegisterData()
{
  for (int i = 0; i < registerCount; ++i)
  {
    printRegisterValue(i);
  }
  return true;
}
