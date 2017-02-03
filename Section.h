#include <vector>
#include <string>
#include "Book.h"

enum Status { required=0, optional=1 };

struct BookAssignment {
	Status status;
	Book* book;
};

class Section {
public:
	Section(int _section_num) 
	: section_number(_section_num) {}

	void assignBook(int s, Book* b);
	std::string getBooks();

private:
	int section_number;
	std::vector<BookAssignment> books;
};
