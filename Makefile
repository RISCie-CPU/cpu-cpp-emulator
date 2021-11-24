CPP=g++
CFLAGS=-I.


test:
	$(CPP) -o main.out src/instruction_memory.cpp src/main.cpp
	./main.out tests/bin/program.bin
