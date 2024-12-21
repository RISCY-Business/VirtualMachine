#pragma once
#include "../defines.h"

// - - - NOTE: everything here is configurable
#define PROCESSOR_RAM_SIZE_BYTES                    (128 * 1024)
#define CLOCK_FREQUENCY_HERTZ                       (4 * 4 * 4)
#define COMPUTOR_NAME                               "Komputor"

// - - - WARNING: do not change for the love of God
#define REGISTER_SIZE_BYTES                         (1 * 4 * 1)
#define RAM_MODULE_REGISTERS                        (PROCESSOR_RAM_SIZE_BYTES / REGISTER_SIZE_BYTES)
#define RAM_ADDRESSIBLE_BITS                        (RAM_MODULE_REGISTERS - 1)
#define PROCESSOR_INSTRUCTION_MEMORY_SIZE_BYTES     PROCESSOR_RAM_SIZE_BYTES
