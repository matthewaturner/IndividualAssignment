#include "Book.h"

Book::Book(int _isbn, std::string _title) {
	isbn = _isbn;
	title = _title;
	author = "unknown";
	edition = 1;
	month = 0;
	year = 0;
}

void Book::setCost(std::string _format, double _cost) {
	prices[_format] = _cost;
}

void Book::print(std::ostream& os) {
	// print book itself
	os << isbn << " " << title << " (Edition " << edition << ") by "
	   << author << ", Published " << getDate() << std::endl;
	// set precision of double values
	os << std::setprecision(2) << std::fixed;
	// print book prices
	os << "  Prices: ";
	for(auto& elem : prices) {
		os << elem.first << "=" << elem.second << " ";
	}
	os << std::endl;
}
