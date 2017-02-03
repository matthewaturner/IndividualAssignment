#include "Catalog.h"

int Catalog::defineBook(int _isbn, std::string _title) {
	books[_isbn] = Book{_isbn, _title};
	return 0;
}

int Catalog::defineBookAuthor(int _isbn, std::string _author) {
	books[_isbn].setAuthor(_author);
	return 0;
}

int Catalog::defineBookEdition(int _isbn, int _edition) {
	books[_isbn].setEdition(_edition);
	return 0;
}

int Catalog::defineBookDate(int _isbn, int _month, int _year) {
	books[_isbn].setDate(_month, _year);
	return 0;
}

std::string Catalog::printAllBooks() {
	std::string result;
	for(auto const& elem : books) {
		Book b = elem.second;
		result += b.print();
		result += "\n";
	}
	
	return result;
}

