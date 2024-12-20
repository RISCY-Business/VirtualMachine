#include "../virtualMachineInterface/include.h"
#include "../library/include/logger.h"

const char* registerNames[registerCount] =
{
  "Zero",
  "Return Address",
  "Stack Pointer",
  "Global Pointer",
  "Thread Pointer",
  "Temp/Alt Link",
  "Temporary1",
  "Temporary2",
  "Saved/Frame Pointer",
  "Saved Register1",
  "Arg/Return0",
  "Arg/Return1",
  "Arguments2",
  "Agruments3",
  "Arguments4",
  "Arguments5",
  "Arguments6",
  "Arguments7",
  "Saved Register2",
  "Saved Register3",
  "Saved Register4",
  "Saved Register5",
  "Saved Register6",
  "Saved Register7",
  "Saved Register8",
  "Saved Register9",
  "Saved Register10",
  "Saved Register11",
  "Temporary3",
  "Temporary4",
  "Temporary5",
  "Temporary6"
};


const char* getRegisterName(RegisterABI REGISTER)
{
  if (REGISTER == registerCount)
  {
    FORGE_LOG_ERROR("Index out of bounds in getting register Name. Index : %d", REGISTER);
    return NULL;
  }

  return registerNames[REGISTER]; 
}

const u32 readRegister(RegisterABI REGISTER)
{
  if (REGISTER == registerCount)
  {
    FORGE_LOG_ERROR("Index out of bounds in reading register. Index : %d", REGISTER);
    return -1;
  }

  return computor.registers[REGISTER].value;
}

bool writeRegister(RegisterABI REGISTER, const u32 VALUE)
{
  if (REGISTER == zero)
  {
    FORGE_LOG_ERROR("Cannot write to hardcoded zero register (x0). It will always be 0");
    return false;
  }

  if (REGISTER == registerCount)
  {
    FORGE_LOG_ERROR("Index out of bounds in reading register. Index : %d", REGISTER);
    return false;
  }

  computor.registers[REGISTER].busValue = VALUE;

  if (!isRisingEdge()) FORGE_LOG_WARNING("Writing to register ABI : %d NAME: %s without a rising edge. Write will occur on the next clock rise", REGISTER, getRegisterName(REGISTER));
  computor.registers[REGISTER].busValue = VALUE;
  return true;
}

void printRegisterValue(RegisterABI REGISTER)
{
  if (REGISTER == registerCount)
  {
    FORGE_LOG_ERROR("Index out of bounds in printing register data. Index : %d", REGISTER);
    return;
  }
  FORGE_LOG_DEBUG("%-20s x%-2d --> %02X", getRegisterName(REGISTER), REGISTER, readRegister(REGISTER));
}

void updateRegisters()
{
  if (!isRisingEdge()) return;
  for (int i = 0; i < registerCount; ++i)
  {
    computor.registers[i].value = computor.registers[i].busValue;
  }
}
