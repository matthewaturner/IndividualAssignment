#include <vector>
#include <string>
#include <iostream>
#include "Book.h"

enum Status { required=0, optional=1 };

struct BookAssignment {
	Status status;
	Book* book;
};

class Section {
public:
	Section()
	: section_number() {}

	Section(int _sn) 
	: section_number(_sn) {}

	std::vector<Book> getBooks();
	void assignBook(int s, Book* b);
	void printBooks(std::ostream& os);
	int minCost();
	int maxCost();

private:
	int section_number;
	std::vector<BookAssignment> books;
};
