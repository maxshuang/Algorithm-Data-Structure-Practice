# Makefile

# Compiler
CC = g++

# include
TEST_INCLUDE = -I ../../helper/Catch2/include -I ../
INCLUDE = -I /usr/include/c++/9 -I /usr/include/x86_64-linux-gnu/c++/9 -I ../../helper $(TEST_INCLUDE)

# Compiler flags
CFLAGS = -g -std=c++11 -Wall -Wextra $(INCLUDE)

# Source files
SOURCES = $(wildcard *.cpp) ../undirected_graph/undirected_graph.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Output file
OUTPUT = test

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(OUTPUT)
