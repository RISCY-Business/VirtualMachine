#pragma once 

#include "../defines.h"
#include "../virtualMachineInterface/include.h"
#include "../library/include/expect.h"
#include <unistd.h>


// - - - test computor
u8 computorShouldStart();
u8 computorShouldStop();
u8 computorShouldNotStart();
u8 computorShouldNotStop();
u8 computorShouldReadFile();
u8 computorShouldRestart();
u8 computorShouldNotReadFile();

// - - - test clock 
u8 runComputorFor50UpdatesAndPrintEdges();

// - - - test register file 
u8 successfullyPrintAllRegisterNames();
u8 successfullyFailAtGettingRegisterName();
u8 checkAllRegistersZero();
u8 writeAllRegisters();
u8 successfullyPrintAllRegisterData();
u8 failAtWriteAtZero();
u8 writeAllRegistersAtLowEdge();

// - - - test ram 
u8 checkAddressToRegisterIndexConversion();
u8 checkRegisterIndexToAddressConversion();
u8 checkResetRam();
u8 checkResetMemoryRam();
u8 checkReadRam();
u8 checkReadMemoryRam();
u8 checkWriteRam();
