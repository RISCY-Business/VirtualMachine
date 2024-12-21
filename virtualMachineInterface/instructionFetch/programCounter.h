#pragma once 
#include "../../defines.h"

/*
@brief:     adds 4 to the program counter 
*/
FORGE_API void  updateProgramCounter();

/*
@brief:     sets the value of program counter to ADDRESS.
*/
FORGE_API bool  setProgramCounter(u32 ADDRESS);

/*
@brief:     returns the value of program counteri
*/
FORGE_API u32   getProgramCounter();

/*
@brief:     returns the current instruction that the program counter points to
*/
FORGE_API u32   getInstruction();
