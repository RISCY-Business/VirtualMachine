cd ..
clang -g                            \
  tests/allTest.c                   \
  tests/computorTest.c              \
  tests/registerTest.c              \
  tests/ramTest.c                   \
  tests/programCounterTest.c        \
                                    \
  virtualMachine/computor.c         \
  virtualMachine/core/clock.c       \
  virtualMachine/core/registers.c   \
  virtualMachine/core/ram.c         \
                                    \
  virtualMachine/instructionFetch/programCounter.c \
                                    \
  library/implement/logger.c        \
  library/implement/testManager.c   \
  library/implement/filesystem.c    \
  -o tests/allTest &&               \
cd tests &&                         \
clear &&                            \
./allTest
cd ..
