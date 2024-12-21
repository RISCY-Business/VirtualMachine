#include "../../virtualMachineInterface/include.h"
#include "../../library/include/logger.h"

u32 convertAddressToRegisterIndex(u32 ADDRESS)
{
  // - - - shift the index forward 2 bits.
  u32 registerIndex = (ADDRESS >> 2);
  
  if (registerIndex >= RAM_MODULE_REGISTERS)
  {
    FORGE_LOG_ERROR("Invalid address : 0x%08X", ADDRESS);
    return -1;
  }

  return registerIndex;
}

u32 convertRegisterIndexToAddress(u32 REGISTER_INDEX)
{
  if (REGISTER_INDEX >= RAM_MODULE_REGISTERS)
  {
      FORGE_LOG_ERROR("Invalid register index: %u", REGISTER_INDEX);
      return -1; 
  }

  // - - - Shift the index back to the address space and return the result
  return REGISTER_INDEX << 2;
}

void resetRam()
{
  computor.ram.busValue             = 0;
  computor.ram.busRegisterIndex     = 0;
  for (int i = 0; i < RAM_MODULE_REGISTERS; ++i)
  {
    Register* reg                   = &computor.ram.registers[i];
    reg->value                      = 0;
    reg->busValue                   = 0;
  }
}


void resetMemoryRam()
{
  computor.memRam.busValue          = 0;
  computor.memRam.busRegisterIndex  = 0;
  for (int i = 0; i < RAM_MODULE_REGISTERS; ++i)
  {
    Register* reg                   = &computor.memRam.registers[i];
    reg->value                      = 0;
    reg->busValue                   = 0;
  }
}


u32 readRam(u32 ADDRESS)
{
  u32 registerIndex = convertAddressToRegisterIndex(ADDRESS);

  if (registerIndex == -1)
  {
    return -1;
  }

  computor.ram.busRegisterIndex = registerIndex;
  return computor.ram.registers[registerIndex].value;
}


u32 readMemoryRam(u32 ADDRESS)
{
  u32 registerIndex = convertAddressToRegisterIndex(ADDRESS);

  if (registerIndex == -1)
  {
    return -1;
  }

  computor.memRam.busRegisterIndex = registerIndex;
  return computor.memRam.registers[registerIndex].value;
}


bool writeRam(u32 ADDRESS, u32 VALUE)
{
  u32 registerIndex = convertAddressToRegisterIndex(ADDRESS);

  if (registerIndex == -1)
  {
    return false;
  }
  
  computor.ram.busRegisterIndex = registerIndex;
  computor.ram.busValue         = VALUE;
  if (isRisingEdge())
  {
    computor.ram.registers[registerIndex].value     = VALUE;
  }
  return true;
}

void updateRam()
{
  if (!isRisingEdge()) return;
  computor.ram.registers[computor.ram.busRegisterIndex].value = computor.ram.busValue;
}
