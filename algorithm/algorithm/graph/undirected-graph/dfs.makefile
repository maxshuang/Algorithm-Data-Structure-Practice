CC = g++
CFLAGS = -std=c++11 -Wall -I ./

all: test_dfsSearch

test_dfsSearch: test_dfsSearch.o dfsSearch.o undirectGraphWithoutWeight.o
	$(CC) $(CFLAGS) -o test_dfsSearch test_dfsSearch.o dfsSearch.o undirectGraphWithoutWeight.o

test_dfsSearch.o: test_dfsSearch.cpp
	$(CC) $(CFLAGS) -c test_dfsSearch.cpp

dfsSearch.o: dfsSearch.cpp dfsSearch.h
	$(CC) $(CFLAGS) -c dfsSearch.cpp

undirectGraphWithoutWeight.o: undirectGraphWithoutWeight.cpp undirectGraphWithoutWeight.h
	$(CC) $(CFLAGS) -c undirectGraphWithoutWeight.cpp

clean:
	rm -rf *.o test_dfsSearch