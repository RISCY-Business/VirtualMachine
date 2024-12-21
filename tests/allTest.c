#include "../library/include/testManager.h"
#include "allTests.h"

int main() 
{
  registerTest(computorShouldStart, "Starts the computor by creating the ram");
  registerTest(computorShouldNotStart, "Try to start the computor a second time and fail");


  // - - - program counter test - - - 
  registerTest(computorShouldNotReadFile, "The file does not exist, the computor should fail to read it");
  registerTest(computorShouldReadFile, "The file does exist its just 0 and 1, read should be successful");
  registerTest(checkProgramCounter0AtStart, "Program Counter should be zero when the computor starts");
  registerTest(checkInstructions, "Check if instruction reading is going properly");
  registerTest(checkUpdateProgramCounter, "Check if updating the program counter works properly");
  registerTest(checkSetProgramCounter, "Check if the program counter is ready for branching");
  registerTest(checkSetProgramCounterFail, "Check if the program counter refuses to branch outside of instruction memory");


  // - - - clock test - - - 

  registerTest(runComputorFor50UpdatesAndPrintEdges, "Check if clock is working properly, includes one visual test");


  // - - - register tests - - - 

  registerTest(successfullyPrintAllRegisterNames, "Print all the register names, one by one");
  registerTest(successfullyFailAtGettingRegisterName, "Fail at getting the name of registers by an index out of bounds and a wild index");
  registerTest(checkAllRegistersZero, "Check if all registers are zero when the computor starts");
  registerTest(writeAllRegisters, "Write values to all registers except the zero register ofcourse");
  registerTest(writeAllRegistersAtLowEdge, "Write values to all registers except the zero register ofcourse at low edge, but fail, the value should be remembered though");
  registerTest(failAtWriteAtZero, "Fail to write at the hardcoded zero register");
  registerTest(successfullyPrintAllRegisterData, "Print all the registers");


  // - - - ram test - - - 

  registerTest(checkAddressToRegisterIndexConversion, "Check if we are successfully translating address to register index");
  registerTest(checkRegisterIndexToAddressConversion, "check if we can go the other way around, from register index to address");
  registerTest(checkWriteRam, "Check if writing to ram happens properly");
  registerTest(checkReadRam, "Check if we can read the values that were written");
  registerTest(checkResetRam, "Check if ram can be reset easily");
  registerTest(checkResetMemoryRam, "Check if memory ram can be reset just as easily");

  registerTest(computorShouldStop, "Stop the computor and free the ram");
  registerTest(computorShouldNotStop, "Try to stop the computor a second time and fail");
  registerTest(computorShouldRestart, "Restart and stop the computor");
  runTests();
  return 0;
}
