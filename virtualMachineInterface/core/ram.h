#pragma once 
#include "../structs.h"

/*
@brief:     Converts address to the ram register index.
@error:     It returns -1 if the address doesnt exist, and an unisgned int with -1, :(
*/
FORGE_API u32 convertAddressToRegisterIndex(u32 ADDRESS);

/*
@brief:     Converts address to the ram register index.
@error:     It returns -1 if the address doesnt exist, and an unisgned int with -1, :(
*/
FORGE_API u32 convertRegisterIndexToAddress(u32 REGISTER_INDEX);

/*
@brief:     Just sets all the bits in all the registers to 0
*/
FORGE_API void resetRam();

/*
@brief:     Just sets all the bits in all the registers to 0 of the instruction memory
@error:     Returns false on fail
*/
FORGE_API void resetMemoryRam();

/*
@brief:     Give it an adress, it will give you the memory stored at that location
@error:     It returns -1 if the register doesnt exist, and an unisgned int with -1, :(
*/
FORGE_API u32  readRam(u32 ADDRESS);

/*
@brief:     Give it an adress, it will give you the memory stored at that location from the memory instruction
@error:     It returns -1 if the register doesnt exist, and an unisgned int with -1, :(
*/
FORGE_API u32  readMemoryRam(u32 ADDRESS);

/*
@brief:     Given an address that is correct and a value, it will store the value 
            on the bus of the correct register. On the next clock pulse, it 
            will sync up with the value.
@error:     Returns false on the if the address is not accessible
*/
FORGE_API bool writeRam(u32 ADDRESS, u32 VALUE);

/*
@brief:     If the clock pulse is a rising edge, the ram will sync up with  
            the value at the bus.
*/
FORGE_API void updateRam();
