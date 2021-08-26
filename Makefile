CPP=g++
CFLAGS=-I.

%.o: %.cpp $(DEPS)
	$(CPP) -c -o $@ $< $(CFLAGS)

test: src/instruction_memory.o
	$(CPP) -o tests/instruction_memory ./src/instruction_memory.o tests/instruction_memory.cpp
	tests/instruction_memory tests/bin/binfile 0xc