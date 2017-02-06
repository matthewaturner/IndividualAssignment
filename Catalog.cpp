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

	std::cout << "got here " << std::endl;
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

	courses[dept_code+std::to_string(course_num)].assignBook(sect_num, ro, b);
	return 0;
}

/* ------------------------------------------------------------------------- */
/*      Printing Functions                                                   */
/* ------------------------------------------------------------------------- */

int Catalog::printBook(int isbn, std::ostream& os) {
	if(books.find(isbn) == books.end())
		return 1;

	books[isbn].print(os);
	os << "  Prices: ";
	books[isbn].printPrices(os);
	os << std::endl;
	return 0;
}


void Catalog::printAllBooks(std::ostream& os) {
	os << "All Books: " << std::endl;
	for(auto const& elem : books) {
		Book b = elem.second;
		b.print(os);
	}
}

void Catalog::printCourses(std::ostream& os) {
	os << "All Courses: " << std::endl;
	for(auto const& elem : courses) {
		Course c = elem.second;
		c.print(os);
	}
}

int Catalog::printBooksBySection(std::string dept_code, int course_num, 
		int sect_num, std::ostream& os) {
	if(courses.find(dept_code+std::to_string(course_num)) == courses.end())
		return 1;
	
	Course c = courses[dept_code+std::to_string(course_num)];
	auto sections = c.getSections();

	if(sections.find(sect_num) == sections.end())
		return 2;

	os << "Books for " << dept_code << " " << course_num << " " <<
		sect_num << ": " << std::endl;
	sections[sect_num].printBooks(os);
	return 0;
}

int Catalog::printBooksByCourse(std::string dept_code, int course_num,
		std::ostream& os) {
	if(courses.find(dept_code+std::to_string(course_num)) == courses.end())
		return 1;

	Course c = courses[dept_code+std::to_string(course_num)];

	for(auto const& elem : c.getSections()) {
		Section s = elem.second;
		os << "Section " << elem.first << ": ";
		s.printBooks(os);
	}
	return 0;

}

int Catalog::printBooksByDepartment(std::string dept_code, std::ostream& os) {
	os << "Books in department '" << dept_code << "': " << std::endl;
	std::set<Book> book_list;

	for(auto const& elem : courses) {
		Course c = elem.second;
		if (c.getDepartmentCode() == dept_code) {
			for(auto const& elem2 : c.getSections()) {
				Section s = elem2.second;
				for(Book b : s.getBooks()) {
					book_list.insert(b);
				}
			}
		}
	}

	for(Book b : book_list) {
		b.print(os);
	}
	return 0;
}

int Catalog::printBooksByDate(std::string date, std::ostream& os) {
	os << "Books published on " << date << ": " << std::endl;
	std::set<Book> book_list;

	for(auto const& elem : books) {
		Book b = elem.second;
		if (b.getDate() == date) {
			book_list.insert(b);
		}
	}

	for(Book b : book_list) {
		b.print(os);
	}
	return 0;
}

void Catalog::printAverageBookCosts(std::string dept_code, std::ostream& os) {
	os << "Average book cost in department '" << dept_code << "': " 
		<< std::endl;

	double min_total = 0;
	double max_total = 0;
	int num_sections_min = 0;
	int num_sections_max = 0;
	
	for(auto const& elem : courses) {
		Course c = elem.second;
		if(c.getDepartmentCode() == dept_code) {
			for(auto const& elem2 : c.getSections()) {
				Section s = elem2.second;
				if(s.minCost() != -1) {
					min_total += s.minCost();
					num_sections_min++;
				}
				if(s.maxCost() != -1) {
					max_total += s.maxCost();
					num_sections_max++;
				}
			}
		}
	}

	double min_average = (min_total != 0) ? min_total / num_sections_min : 0;
	double max_average = (max_total != 0) ? max_total / num_sections_max : 0;

	os << "  Average Min: " << min_average << std::endl
	   << "  Average Max: " << max_average << std::endl;
}
