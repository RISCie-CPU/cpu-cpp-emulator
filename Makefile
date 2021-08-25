CPP=g++
CFLAGS=-I.
DEPS = hellomake.h

%.o: %.cpp $(DEPS)
	$(CPP) -c -o $@ $< $(CFLAGS)

test: src/instruction_memory.o
	$(CPP) -o tests/instruction_memory ./src/instruction_memory.o tests/instruction_memory.cpp