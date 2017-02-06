#include <iostream>
#include <map>
#include <set>
#include "Department.h"

class Catalog {
public:
	Catalog() 
	: books(), courses() {}
	
	// Book Functions
	int defineBook(int isbn, std::string title);
	int defineBookAuthor(int isbn, std::string author);
	int defineBookEdition(int isbn, int edition);
	int defineBookDate(int isbn, int month, int year);
	int defineBookCost(int isbn, std::string format, double cost);

	// Other Functions
	int defineCourse(std::string dept_code, int course_num, std::string course_name);
	int assignBook(int isbn, std::string dept_code, int course_num, int sect_num,
			int ro);

	// Printing Functions
	int printBook(int isbn, std::ostream& os);
	void printAllBooks(std::ostream& os);
	void printCourses(std::ostream& os);
	void printAverageBookCosts(std::string dept_code, std::ostream& os);
	int printBooksBySection(std::string dept_code, int course_num, 
			int sect_num, std::ostream& os);
	int printBooksByCourse(std::string dept_code, int course_num,
			std::ostream& os);
	int printBooksByDepartment(std::string dept_code, std::ostream& os);
	int printBooksByDate(std::string date, std::ostream& os);
	

private:
	std::map<int, Book> books;
	std::map<std::string, Course> courses;
};
