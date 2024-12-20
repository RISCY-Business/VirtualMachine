cd ..
clang tests/allTest.c tests/computorTest.c tests/registerTest.c virtualMachine/computor.c virtualMachine/clock.c virtualMachine/registers.c library/implement/logger.c library/implement/testManager.c library/implement/filesystem.c -o tests/allTest
cd tests 
clear
./allTest 
cd ..
