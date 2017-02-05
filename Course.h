#include <string>
#include <iostream>
#include <map>
#include "Section.h"

class Course {
public:
	// Constructors
	Course()
	: department_code(), course_number(), course_name() {}

	Course(std::string _deptcode, int _cnum, std::string _cname) 
	: department_code(_deptcode), course_number(_cnum), course_name(_cname) {}

	// Functions
	void print(std::ostream& os);
	int assignBook(int sect_num, int ro, Book* b);
private:
	std::string department_code;     // 4 character code e.g. "csce"
	int course_number;               // 3 digit course number
	std::string course_name;         // short name for course
	std::map<int, Section> sections; // sections in course
};
