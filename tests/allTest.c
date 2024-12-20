#include "../library/include/testManager.h"
#include "allTests.h"

int main() 
{
  registerTest(computorShouldStart, "Starts the computor by creating the ram");
  registerTest(computorShouldNotStart, "Try to start the computor a second time and fail");
  registerTest(runComputorFor50UpdatesAndPrintEdges, "Check if clock is working properly, includes one visual test");


  // - - - register tests - - - 

  registerTest(successfullyPrintAllRegisterNames, "Print all the register names, one by one");
  registerTest(successfullyFailAtGettingRegisterName, "Fail at getting the name of registers by an index out of bounds and a wild index");
  registerTest(checkAllRegistersZero, "Check if all registers are zero when the computor starts");
  registerTest(writeAllRegisters, "Write values to all registers except the zero register ofcourse");
  registerTest(writeAllRegistersAtLowEdge, "Write values to all registers except the zero register ofcourse at low edge, but fail, the value should be remembered though");
  registerTest(failAtWriteAtZero, "Fail to write at the hardcoded zero register");
  registerTest(successfullyPrintAllRegisterData, "Print all the registers");

  registerTest(computorShouldNotReadFile, "The file does not exist, the computor should fail to read it");
  registerTest(computorShouldReadFile, "The file does exist its just 0 and 1, read should be successful");
  registerTest(computorShouldStop, "Stop the computor and free the ram");
  registerTest(computorShouldNotStop, "Try to stop the computor a second time and fail");
  registerTest(computorShouldRestart, "Restart and stop the computor");
  runTests();
  return 0;
}
