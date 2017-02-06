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

	// Getters
	std::string getDepartmentCode() { return department_code; }
	int getCourseNumber() { return course_number; }
	std::string getCourseName() { return course_name; }

	// Functions
	std::map<int, Section> getSections();
	int assignBook(int sect_num, int ro, Book* b);
	void print(std::ostream& os);
private:
	std::string department_code;     // 4 character code e.g. "csce"
	int course_number;               // 3 digit course number
	std::string course_name;         // short name for course
	std::map<int, Section> sections; // sections in course
};
