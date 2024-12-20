#pragma once 
#include "../defines.h"

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

FORGE_API const char* getRegisterName         (RegisterABI REGISTER);

FORGE_API const u32   readRegister            (RegisterABI REGISTER);

FORGE_API bool        writeRegister           (RegisterABI REGISTER, const u32 VALUE);

FORGE_API void        updateRegisters         ();

FORGE_API void        printRegisterValue      (RegisterABI REGISTER);
