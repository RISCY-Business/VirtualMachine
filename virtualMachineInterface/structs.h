#pragma once
#include "../defines.h"
#include "proccessorDefaults.h"

typedef struct Register
{
  u32     value;
  u32     busValue;
} Register;


typedef struct Computor
{
  u8*       ram;
  u8*       program;
  Register  registers[32];
  bool      clock;
} Computor;


