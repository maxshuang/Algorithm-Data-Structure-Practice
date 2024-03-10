CC = g++
CFLAGS = -std=c++11 -Wall

INCLUDE = -I /usr/include/c++/9 -I /usr/include/x86_64-linux-gnu/c++/9 
TARGET = main
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)