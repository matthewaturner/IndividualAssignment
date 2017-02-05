#include "Section.h"

void Section::assignBook(int s, Book* b) {
	BookAssignment ba = {Status(s), b};
	books.push_back(ba);
}

void Section::printBooks(std::ostream& os) {
	for(BookAssignment b : books) {
		b.book->print(os);
	}
}
