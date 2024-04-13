CC = g++
INCLUDE= -I /home/maxshuang/project/std-libs/boost_1_84_0
CFLAGS = -std=c++11 -Wall -g $(INCLUDE)

TARGET = copy_on_write
SRC = copy_on_write2.cpp
#SRC = basic_map.cpp

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
