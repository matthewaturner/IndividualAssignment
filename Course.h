#include <string>

class Course {
public:
	Course(std::string _dept_code, int _course_num) 
	: department_code(_dept_code), course_number(_course_num) {}

private:
	std::string department_code;
	int course_number;
};
