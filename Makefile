CPP=g++
CFLAGS=-I.


test:
	$(CPP) -o main.out src/register.cpp src/main.cpp src/program_counter.cpp src/instruction_memory.cpp src/control_unit.cpp
	./main.out tests/bin/program.bin
