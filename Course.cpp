#include "Course.h"

std::map<int, Section> Course::getSections() {
	return sections;
}

int Course::assignBook(int sect_num, int ro, Book* b) {
	sections[sect_num].assignBook(ro, b);
}

void Course::print(std::ostream& os) {
	os << department_code << " " << course_number << 
		": " << course_name << std::endl;
}
