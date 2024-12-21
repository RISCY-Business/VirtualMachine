#include "../../virtualMachineInterface/include.h"
#include "../../library/include/logger.h"
#include <bits/time.h>
#include <time.h>
#include <unistd.h>

static bool         lastClock       = false;
static u64          lastPulseTime   = 0;


u64 getCurrentTimeMicros()
{
  // - - - return current time precisely in microseconds
  struct timespec   ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (u64)(ts.tv_sec) * 1000000 + (ts.tv_nsec / 1000);
}

void updateClock()
{
  // - - - do time keepinG
  f64 period        = 100000.0 / (CLOCK_FREQUENCY_HERTZ);
  u64 currentTime   = getCurrentTimeMicros();
  u64 elapsedTime   = currentTime - lastPulseTime;

  // - - - spin wait for the remaining time 
  if (elapsedTime < period)
  {
    usleep(period - elapsedTime);
  }
  else 
  {
    FORGE_LOG_WARNING("%s running too slow. Clock Pulse delayed! Elapsed time: %llu us", COMPUTOR_NAME, elapsedTime);
  }

  // - - - update the variables
  lastClock         = computor.clock;
  computor.clock    = !computor.clock;
  lastPulseTime     = getCurrentTimeMicros();
}

bool isClockLow()
{
  return !computor.clock;
}

bool isClockHigh()
{
  return computor.clock;
}

bool isRisingEdge()
{
  return computor.clock && !lastClock;
}

bool isFallingEdge()
{
  return !computor.clock && lastClock;
}
