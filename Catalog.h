#include <map>
#include "Department.h"

class Catalog {
public:
	Catalog() 
	: books(), courses() {}

	int defineBook(int _isbn, std::string _title);
	int defineBookAuthor(int _isbn, std::string _author);
	int defineBookEdition(int _isbn, int _edition);
	int defineBookDate(int _isbn, int _month, int _year);

	std::string printAllBooks();

private:
	std::map<int, Book> books;
	std::map<std::string, Course> courses;
};
