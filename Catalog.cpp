#include "Catalog.h"

/* ------------------------------------------------------------------------- */
/*      Book Functions                                                       */
/* ------------------------------------------------------------------------- */

int Catalog::defineBook(int isbn, std::string title) {
	books[isbn] = Book{isbn, title};
	return 0;
}

int Catalog::defineBookAuthor(int isbn, std::string author) {
	if(books.find(isbn) == books.end())
		return 1;

	books[isbn].setAuthor(author);
	return 0;
}

int Catalog::defineBookEdition(int isbn, int edition) {
	if(books.find(isbn) == books.end())
		return 1;

	books[isbn].setEdition(edition);
	return 0;
}

int Catalog::defineBookDate(int isbn, int month, int year) {
	if(books.find(isbn) == books.end())
		return 1;

	books[isbn].setDate(month, year);
	return 0;
}

int Catalog::defineBookCost(int isbn, std::string format, double cost) {
	if(books.find(isbn) == books.end())
		return 1;

	books[isbn].setCost(format, cost);
	return 0;
}

/* ------------------------------------------------------------------------- */
/*      Other Functions                                                      */
/* ------------------------------------------------------------------------- */

int Catalog::defineCourse(std::string dept_code, int course_num, 
		std::string course_name) {

	Course c = {dept_code, course_num, course_name};
	courses[dept_code+std::to_string(course_num)] = c;
	return 0;
}

int Catalog::assignBook(int isbn, std::string dept_code, int course_num,
		int sect_num, int ro) {
	if(books.find(isbn) == books.end())
		return 1;

	Book* b = &books[isbn];

	if(courses.find(dept_code+std::to_string(course_num)) == courses.end())
		return 2;

	Course* c = &courses[dept_code+std::to_string(course_num)];
	return c->assignBook(sect_num, ro, b) ? 3 : 0;
}

/* ------------------------------------------------------------------------- */
/*      Printing Functions                                                   */
/* ------------------------------------------------------------------------- */

int Catalog::printBook(int isbn, std::ostream& os) {
	if(books.find(isbn) == books.end())
		return 1;

	books[isbn].print(os);
	return 0;
}


void Catalog::printAllBooks(std::ostream& os) {
	for(auto const& elem : books) {
		Book b = elem.second;
		b.print(os);
	}
}

void Catalog::printCourses(std::ostream& os) {
	for(auto const& elem : courses) {
		Course c = elem.second;
		c.print(os);
	}
}





