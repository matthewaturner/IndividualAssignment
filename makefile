
all: lib

Book.o: Book.h Book.cpp
	g++ -std=c++11 -c -g Book.h Book.cpp 

Library.o: Library.cpp
	g++ -std=c++11 -c -g Library.cpp

lib: Library.o Book.o
	g++ -std=c++11 -o lib Library.o Book.o

clean:
	rm *.o *.gch
