#include <string>
#include <map>
#include "Section.h"

class Course {
public:
	Course()
	: department_code(), course_number() {}

	Course(std::string _dept_code, int _course_num) 
	: department_code(_dept_code), course_number(_course_num) {}

private:
	std::string department_code;
	int course_number;
	std::map<int, Section> sections;
};
