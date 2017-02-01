#include <map>
#include "Book.h"
#include "Courses.h"

class Catalog {
public:

private:
	std::map<int, Book> books;
	std::map<std::string, Course> courses;
};
