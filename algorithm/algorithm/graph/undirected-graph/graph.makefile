# Makefile

# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++17 -Wall -Wextra -I /usr/include/c++/9 -I /usr/include/x86_64-linux-gnu/c++/9

# Source files
SOURCES = undirectGraphWithoutWeight.c testUndirectGraphWithoutWeight.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Output file
OUTPUT = testUG

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(OUTPUT)
