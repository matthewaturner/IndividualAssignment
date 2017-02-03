#include <string>
#include <map>
#include "Course.h"

class Department {
public:
	Department()
	: department_code() {}

	Department(std::string _dept_code)
	: department_code(_dept_code) {}

	int addCourse(Course c);

private:
	std::string department_code;
	std::map<int, Course> courses;
};
