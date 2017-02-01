#include <vector>
#include "Book.h"

class Section {
public:
	Section(int _section_num) 
	: section_number(_section_num) {}

private:
	int section_number;
	std::vector<Book> required_books, optional_books;
};
