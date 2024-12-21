#pragma once 
#include "../structs.h"

//- - -  NOTE: This is just the indexes of the registers in the register file in the computor
typedef enum RegisterABI
{
  zero,
  ra,
  sp,
  gp,
  tp,
  t0,
  t1,
  t2,
  s0_fp,
  s1,
  a0,
  a1,
  a2,
  a3,
  a4,
  a5,
  a6,
  a7,
  s2,
  s3,
  s4,
  s5,
  s6,
  s7,
  s8,
  s9,
  s10,
  s11,
  t3,
  t4,
  t5,
  t6,
  registerCount,
} RegisterABI;

/*
@brief:     This gives the register's name as a string if needed
@error:     It returns NULL if the register doesnt exist
*/
FORGE_API const char* getRegisterName         (RegisterABI REGISTER);

/*
@brief:     This returns whatever value is stored in the register at the moment
@error:     It returns -1 if the register doesnt exist, and an unisgned int with -1, :(
*/
FORGE_API const u32   readRegister            (RegisterABI REGISTER);

/*
@brief:     This writes the value to the register's bus. At the next clock pulse, the register will sync up with that value 
@error:     It returns false if the register fails to write, such as in case of non-existant or zero register
*/
FORGE_API bool        writeRegister           (RegisterABI REGISTER, const u32 VALUE);

/*
@brief:     At a rising edge, the register syncs up with the value at the bus 
@error:     It is not the responsibility of this function to check if it is a rising edge on the clock, but the responsibility
            of the function that calls it 
*/
FORGE_API void        updateRegister          (Register* REGISTER);

/*
@brief:     This calls updateRegister for all registers in the computor's register file
*/
void                  updateRegisters         ();

/*
@brief:     This can print the value of any register in the register file
*/
FORGE_API void        printRegisterValue      (RegisterABI REGISTER);
