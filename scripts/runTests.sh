cd ..
clang                               \
  tests/allTest.c                   \
  tests/computorTest.c              \
  tests/registerTest.c              \
  tests/ramTest.c                   \
                                    \
  virtualMachine/computor.c         \
  virtualMachine/clock.c            \
  virtualMachine/registers.c        \
  virtualMachine/ram.c              \
                                    \
  library/implement/logger.c        \
  library/implement/testManager.c   \
  library/implement/filesystem.c    \
  -o tests/allTest &&               \
cd tests &&                         \
clear &&                            \
./allTest
cd ..
