# Makefile to recursively compile all .cpp files in subdirectories

INCLUDE = -I /usr/include/c++/9 -I /usr/include/x86_64-linux-gnu/c++/9 -I ./Catch2/include

# Compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11 $(INCLUDE)

# Linker flags
LDFLAGS =

# Target name for the executable
TARGET = test

# Directories to exclude from the search
EXCLUDE_DIRS = Catch2 structure slice-window random-pick linked-list greedy-algorithm 

# Function to check if a .cpp file should be excluded based on EXCLUDE_DIRS
is_excluded = $(if $(filter $(EXCLUDE_DIRS),$(subst /, ,$1)),$1,)

# Recursive wildcard function that finds all .cpp files in subdirectories
rwildcard = $(shell find . -type f -name '*.cpp')

# Get all .cpp files in the current directory and subdirectories
ALL_SRC = $(call rwildcard,.,*.cpp)

# Filter out .cpp files that contain any of the substrings in EXCLUDE_DIRS
# Using is_excluded function to directly filter out files in ALL_SRC
SRC := $(foreach file,$(ALL_SRC),$(if $(call is_excluded,$(file)),,$(file)))

# Convert .cpp files to .o files
OBJ = $(SRC:.cpp=.o)

# Default rule to build the target
all: $(TARGET)

# Link the target with all object files
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

# Pattern rule for compiling .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean all object files and the executable
clean:
	rm -f $(OBJ) $(TARGET)

print-src:
	@echo "Source files:"
	echo $(SRC)

.PHONY: all clean print-src