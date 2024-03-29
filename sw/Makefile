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
DEBUG = 0
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
CPP_SOURCES += $(wildcard app/src/*.cpp)

########################################
# Tools
########################################
CPP = g++

########################################
# Flags for compiler
########################################

# CPP defines
CPP_DEFS =

ifeq ($(DEBUG), 1)
  CPP_DEFS += -DDEBUG=1
endif

# CPP includes
CPP_INCLUDES = \
-Iapp/inc \
"-Imodules/olc/OneLoneCoder/PGE App.xctemplate"

CPP_FLAGS = -std=c++17 $(OPT) $(CPP_INCLUDES) $(CPP_DEFS)

ifeq ($(DEBUG), 1)
    CPP_FLAGS += --debug
endif

# Generate dependency information
CPP_FLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

########################################
# Flags for linker
########################################

LIBS = -lpng

ifeq ($(OS),Windows_NT)
    exit
else
    UNAME := $(shell uname)
    ifeq ($(UNAME),Linux)
        LIBS += -lX11 -lGL -lpthread
    endif
    ifeq ($(UNAME),Darwin)
        LIBS += -framework OpenGL -framework GLUT -framework Carbon
    endif
endif

LDFLAGS = $(LIBS)

#######################################
# Build the application
#######################################

# Default action: build all
all: $(BUILD_DIR)/$(TARGET)

# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	@$(CPP) -c $(CPP_FLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJECTS) Makefile
	@$(CPP) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR):
	mkdir $@

#######################################
# Run
#######################################
run:
	@./$(BUILD_DIR)/$(TARGET) ../bin/color_test.bin

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
