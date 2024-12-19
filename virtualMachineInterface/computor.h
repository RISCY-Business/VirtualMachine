#include "structs.h"

static Computor computor;

/*
NOTE: Start computor will try to allocate memory for the ram to the computor singleton and initialize it all to 0
The function returns a true on a success
The function returns a false on a failure
*/
FORGE_API bool startComputor ();

/*
NOTE: Computor will try to free the ram memory of the computor singleton and shut it down
The function returns a true on a success
The function returns a false on a failure
*/
FORGE_API bool stopComputor  ();

/*
NOTE: Computor will try to rewrite its instruction memory with the contents of the file upto the size of the file or 
the instruction memory, whichever is smaller.
It returns true on success 
It returns false on failure such as file not existing or file not being the correct size
*/
FORGE_API bool loadProgram (const char* FILE_PATH);

FORGE_API void printInstructionMemory ();

FORGE_API void printRAM();

/*
NOTE: This is the main computor simulation loop. Its a while true for now (maybe a stop instruction later). It will update 
all its components
*/
FORGE_API void update();
