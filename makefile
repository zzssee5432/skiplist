CC=g++  
CXXFLAGS =--std=c++11 -pthread
skiplist: main.o 
	$(CC) -o main main.o --std=c++11 -pthread 
	rm -f ./*.o


test.o:test.cpp myskiplist.h mutex.h
	$(CC) -c -g  $^  $(CXXFLAGS)
test:test.o
	$(CC) -g -o $@ $^  $(CXXFLAGS)




clean: 
	rm -f ./*.o
