#include "Course.h"

void Course::print(std::ostream& os) {
	os << department_code << " " << course_number << 
		": " << course_name << std::endl;
}

int Course::assignBook(int sect_num, int ro, Book* b) {
	if(sections.find(sect_num) == sections.end())
		return 1;

	sections[sect_num].assignBook(ro, b);
}
