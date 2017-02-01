
all: lib

Book.o: Book.h Book.cpp
	g++ -std=c++11 -c -g Book.h Book.cpp 

Section.o: Section.h Section.cpp
	g++ -std=c++11 -c -g Section.h Section.cpp

Course.o: Course.h Course.cpp
	g++ -std=c++11 -c -g Course.h Course.cpp

Catalog.o: Catalog.cpp
	g++ -std=c++11 -c -g Catalog.cpp

lib: Catalog.o Course.o Section.o Book.o
	g++ -std=c++11 -o lib main.cpp Catalog.o Course.o Section.o Book.o

clean:
	rm *.o *.gch
