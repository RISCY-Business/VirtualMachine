#pragma once 
#include "logger.h"

#define expectShouldBe(EXPECTED, ACTUAL)                                                                                                \
  if ((ACTUAL) != (EXPECTED))                                                                                                           \
  {                                                                                                                                     \
    FORGE_LOG_ERROR("--> EXPECTED %lld, but got: %lld. File: %s:%d.", (long long)(EXPECTED), (long long)(ACTUAL), __FILE__, __LINE__);  \
    return false;                                                                                                                       \
  }

#define expectShouldNotBe(EXPECTED, ACTUAL)                                                                                             \
  if (ACTUAL == EXPECTED)                                                                                                               \
  {                                                                                                                                     \
    FORGE_LOG_ERROR("--> EXPECTED %d != %d, but they are equal. File: %s:%d.", EXPECTED, ACTUAL, __FILE__, __LINE__);                   \
    return false;                                                                                                                       \
  }

#define expectFloatToBe(EXPECTED, ACTUAL)                                                                                               \
  if (((EXPECTED) - (ACTUAL) < -0.001f) || ((EXPECTED) - (ACTUAL) > 0.001f))                                                            \
  {                                                                                                                                     \
    FORGE_LOG_ERROR("--> EXPECTED %f, but got: %f. File: %s:%d.", (EXPECTED), (ACTUAL), __FILE__, __LINE__);                            \
    return false;                                                                                                                       \
  }

#define expectToBeTrue(ACTUAL)                                                                                                          \
  if (ACTUAL != true)                                                                                                                   \
  {                                                                                                                                     \
    FORGE_LOG_ERROR("--> EXPECTED true, but got: false. File: %s:%d.", __FILE__, __LINE__);                                             \
    return false;                                                                                                                       \
  }

#define expectToBeFalse(ACTUAL)                                                                                                         \
  if (ACTUAL != false)                                                                                                                  \
  {                                                                                                                                     \
    FORGE_LOG_ERROR("--> EXPECTED false, but got: true. File: %s:%d.", __FILE__, __LINE__);                                             \
    return false;                                                                                                                       \
  }