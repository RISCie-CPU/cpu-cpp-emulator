########################################
# CPU Emulator Makefile
########################################

########################################
# Target
########################################
TARGET = cpu-emulator

########################################
# Building variables
########################################
# Compile for debugging?
# (1 ... yes, 0 ... no)
DEBUG = 1
# optimization
OPT = -O2

########################################
# Paths
########################################
# Build path
BUILD_DIR = build

######################################
# Source
######################################
# C++ sources
CPP_SOURCES += $(wildcard src/*.cpp)

########################################
# Tools
########################################
CPP = g++

OLC_FLAGS =-lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

########################################
# Flags for compiler
########################################

# CPP defines
C_DEFS =

# CPP includes
CPP_INCLUDES = \
-Iinc

CPP_FLAGS = $(CPP_INCLUDES) $(CPP_DEFS) $(OPT)

ifeq ($(DEBUG), 1)
CPP_FLAGS += --debug
endif

# Generate dependency information
CPP_FLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


# Default action: build all
all: $(BUILD_DIR)/$(TARGET).elf


#######################################
# Build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	@$(CPP) -c $(CPP_FLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	@$(CPP) $(OBJECTS) $(OLC_FLAGS) -o $@

$(BUILD_DIR):
	mkdir $@

#######################################
# Run
#######################################
run:
	@./$(BUILD_DIR)/$(TARGET).elf ../tests/bin/program.bin

#######################################
# Clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)

#######################################
# Build and Run
#######################################
build_and_run: all run

#######################################
# Dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)
