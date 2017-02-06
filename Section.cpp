#include "Section.h"

std::vector<Book> Section::getBooks() {
	std::vector<Book> results;
	for(BookAssignment b : books) { 
		results.push_back(*b.book);
	}

	return results;
}

void Section::assignBook(int s, Book* b) {
	BookAssignment ba = {Status(s), b};
	books.push_back(ba);
}

void Section::printBooks(std::ostream& os) {
	for(BookAssignment b : books) {
		b.book->print(os);
		if(b.status == 0)
			os << "  REQUIRED";
		else
			os << "  OPTIONAL";
		os << std::endl;
	}
}

int Section::minCost() {
	int cost = 0;
	for(BookAssignment ba : books) {
		if(ba.status == 1 && (*ba.book).minCost() != -1)
			cost += (*ba.book).minCost();
	}
	return (cost != 0) ? cost : -1;
}

int Section::maxCost() {
	int cost = 0;
	for(BookAssignment ba : books) {
		if((*ba.book).maxCost() != -1)
			cost += (*ba.book).maxCost();
	}
	return (cost != 0) ? cost : -1;
}
