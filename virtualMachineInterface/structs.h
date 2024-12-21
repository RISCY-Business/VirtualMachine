#pragma once
#include "../defines.h"
#include "proccessorDefaults.h"

typedef struct Register
{
  u32       value;
  u32       busValue;
} Register;

typedef struct RamModule
{
  Register  registers[RAM_MODULE_REGISTERS];
  u32       busValue;
  u32       busRegisterIndex;
} RamModule;

typedef struct Computor
{
  RamModule ram;
  RamModule memRam;
  Register  programCounter;
  Register  registers[32];
  bool      clock;
} Computor;


