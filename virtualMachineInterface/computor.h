#include "structs.h"

// - - - NOTE: this is the heart and soul of the program. The computor that runs everything
static Computor computor;

/*
@brief:     Start computor will try to start the clock, allocate ram, instruction memory, resets registers etc
@error:     The function returns a false on a failure such as memory test fail or not enough ram or god forbid, double start
*/
FORGE_API bool startComputor ();

/*
@brief:     Stops the computor by doing the opposite of start in the reverse order
@error:     The function returns a false on a failure
*/
FORGE_API bool stopComputor  ();

/*
@brief:     Computor will try to rewrite its instruction memory with the contents of the file upto the size of the file or 
            the instruction memory, whichever is smaller.
            Dont think that this reads the program as binary, it reads it as txt file (i.e : 011 (3 bytes) is read as 3)
@error:     It returns false on failure such as file not existing or file not being the correct size
*/
FORGE_API bool loadProgram (const char* FILE_PATH);

/*
@brief:     Simple print the instruction memory
*/
FORGE_API void printInstructionMemory ();

/*
@brief:     Simple print the ram
*/
FORGE_API void printRAM();

/*
@brief:     Simple print the registers
*/
FORGE_API void printRegisters();

/*
@brief:     This is the main computor simulation loop. Its a while true for now (12/21/2024 00:55) (maybe a stop instruction later). It will update 
all its components
*/
FORGE_API void update();
