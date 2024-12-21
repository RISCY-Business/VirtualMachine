#include "allTests.h"
#include "../library/include/testManager.h"

u8 checkAddressToRegisterIndexConversion()
{
  FORGE_LOG_WARNING("This test will cause an error");
  expectShouldBe(0, convertAddressToRegisterIndex(0));
  expectShouldBe(1 ,convertAddressToRegisterIndex(4));
  expectShouldBe(2, convertAddressToRegisterIndex(8));
  expectShouldBe(3, convertAddressToRegisterIndex(12));
  expectShouldBe(RAM_MODULE_REGISTERS - 1, convertAddressToRegisterIndex((RAM_MODULE_REGISTERS - 1) << 2));
  expectShouldBe(-1 , convertAddressToRegisterIndex( 0xFFFFFFFF));

  return true;
}

u8 checkRegisterIndexToAddressConversion()
{
  expectShouldBe(convertRegisterIndexToAddress(0), 0x0000);
  expectShouldBe(convertRegisterIndexToAddress(1), 0x0004);
  expectShouldBe(convertRegisterIndexToAddress(RAM_MODULE_REGISTERS - 1), ((RAM_MODULE_REGISTERS - 1) << 2));
  FORGE_LOG_WARNING("This test will cause an error");
  expectShouldBe(convertRegisterIndexToAddress(RAM_MODULE_REGISTERS), -1);

  return true;
}

u8 checkResetRam()
{
  resetRam();
  for (u32 address = 0; address < PROCESSOR_RAM_SIZE_BYTES; address += 4) 
  {
    expectShouldBe(readRam(address), 0);
  }

  return true;
}

u8 checkResetMemoryRam()
{
  resetMemoryRam();
  for (u32 address = 0; address < PROCESSOR_RAM_SIZE_BYTES; address += 4) 
  {
    expectShouldBe(0, readMemoryRam(address));
  }

  return true;
}

u8 checkWriteRam()
{
  FORGE_LOG_WARNING("This test will cause an error");
  while (!isRisingEdge())
  {
    update();
  }
  expectToBeTrue(isRisingEdge());
  expectToBeTrue(writeRam(0x0000, 0x12345678));
  update();
  expectToBeTrue(writeRam(0x0004, 0x9ABCDEF0));
  expectToBeFalse(writeRam(PROCESSOR_RAM_SIZE_BYTES + 1, 0xDEADBEEF));

  return true;
}

u8 checkReadRam()
{
  FORGE_LOG_WARNING("This test causes an error");
  while (!isRisingEdge())
  {
    update();
  }
  expectToBeTrue(isRisingEdge());
  expectShouldBe(0x9ABCDEF0, readRam(0x0004));
  expectShouldBe(readRam(0x0000), 0x12345678);
  expectShouldBe(readRam(PROCESSOR_RAM_SIZE_BYTES + 1), -1);

  return true;
}
