#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "Catalog.h"

/* ------------------------------------------------------------------------- */
/*       Type Declarations                                                   */
/* ------------------------------------------------------------------------- */

typedef int (*functionPointer)(Catalog&, std::vector<std::string>);
typedef std::map<std::string, functionPointer> func_map;

/* ------------------------------------------------------------------------- */
/*       Helper Functions                                                    */
/* ------------------------------------------------------------------------- */

template<typename Out>
void split(const std::string &s, char delim, Out result) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		if (item != "")
			*(result++) = item;
	}
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

std::string combine(const std::vector<std::string> tokens, int begin, int end) {
	std::string result = tokens[begin];
	for(int i = begin+1; i<end; i++) {
		result += " " + tokens[i];
	}
	return result;
}

/* ------------------------------------------------------------------------- */
/*       Catalog Functions                                                   */
/* ------------------------------------------------------------------------- */

int DefineBook(Catalog& catalog, std::vector<std::string> args) {
	if(args.size() < 3) return 1;

	return catalog.defineBook(stoi(args[1]), combine(args, 2, args.size()));
}

int DefineBookCharacteristic(Catalog& catalog, std::vector<std::string> args) {
	if(args.size() < 4) return 1;

	int rcode;

	switch(args[2][0]) {
		case 'A':
			rcode = catalog.defineBookAuthor(stoi(args[1]), combine(args, 3, args.size()));
			return (rcode) ? 2 : 0;
		case 'E':
			rcode = catalog.defineBookEdition(stoi(args[1]), stoi(args[3]));
			return (rcode) ? 2 : 0;
		case 'D':
			rcode = catalog.defineBookDate(stoi(args[1]), stoi(args[3]), stoi(args[4]));
			return (rcode) ? 2 : 0;
	}
}

int DefineBookCost(Catalog& catalog, std::vector<std::string> args) { 
	if(args.size() < 4) return 1;

	int rcode;

	switch(args[3][0]) {
		case 'N':
			rcode = catalog.defineBookCost(stoi(args[1]), "new", stod(args[2]));
			return (rcode) ? 2 : 0;
		case 'U':
			rcode = catalog.defineBookCost(stoi(args[1]), "used", stod(args[2]));
			return (rcode) ? 2 : 0;
		case 'R':
			rcode = catalog.defineBookCost(stoi(args[1]), "rented", stod(args[2]));
			return (rcode) ? 2 : 0;
		case 'E':
			rcode = catalog.defineBookCost(stoi(args[1]), "electronic", stod(args[2]));
			return (rcode) ? 2 : 0;

		default:
			std::cout << "Bad argument! Options are [NURE]" << std::endl;
			return 4;
	}
}

int PrintBook(Catalog& catalog, std::vector<std::string> args) { 
	if(args.size() < 2) return 1;

	return (catalog.printBook(stoi(args[1]), std::cout)) ? 2 : 0;
}

int PrintAllBooks(Catalog& catalog, std::vector<std::string> args) { 
	std::cout << "All Books: " << std::endl;
	catalog.printAllBooks(std::cout);
	return 0;
}

int PrintBooksByDepartment(Catalog& catalog, std::vector<std::string> args) { return 0; }
int PrintBooksByCourse(Catalog& catalog, std::vector<std::string> args) { return 0; }
int PrintBooksBySection(Catalog& catalog, std::vector<std::string> args) { return 0; }
int PrintBooksByDate(Catalog& catalog, std::vector<std::string> args) { return 0; }
int PrintAverageBookCosts(Catalog& catalog, std::vector<std::string> args) { return 0; }

int DefineCourse(Catalog& catalog, std::vector<std::string> args) {
	if(args.size() < 4) return 1;

	catalog.defineCourse(args[1], stoi(args[2]), combine(args, 3, args.size()));
	return 0;
}

int PrintCourses(Catalog& catalog, std::vector<std::string> args) { 
	std::cout << "All Courses: " << std::endl;
	catalog.printCourses(std::cout);
	return 0;
}

int AssignBook(Catalog& catalog, std::vector<std::string> args) {
	if(args.size() < 6) return 1;

	int rcode;
	switch(args[5][0]) {
		case 'R':
			rcode = catalog.assignBook(stoi(args[1]), args[2], stoi(args[3]), stoi(args[4]), 1);
		case 'O':
			rcode = catalog.assignBook(stoi(args[1]), args[2], stoi(args[3]), stoi(args[4]), 0);
	}
	
	switch(rcode) {
		case 1: return 2;
		case 2: return 3;
		default: return 0;
	}
}

int Comment(Catalog& catalog, std::vector<std::string> args) {
	// this function just lets us have 'comment' commands 
	// which do nothing
	return 0;
}

/* ------------------------------------------------------------------------- */
/*       Main                                                                */
/* ------------------------------------------------------------------------- */

int main() {
	// deals with all the book and class information
	Catalog catalog;

	// relates functions to the first tokens of the inputs
	func_map function_mapping;
	function_mapping["B"]  = &DefineBook;
	function_mapping["D"]  = &DefineBookCharacteristic;
	function_mapping["M"]  = &DefineBookCost;
	function_mapping["C"]  = &DefineCourse;
	function_mapping["A"]  = &AssignBook;
	function_mapping["GC"] = &PrintBooksByCourse;
	function_mapping["GS"] = &PrintBooksBySection;
	function_mapping["GB"] = &PrintBook;
	function_mapping["PB"] = &PrintAllBooks;
	function_mapping["PC"] = &PrintCourses;
	function_mapping["PY"] = &PrintBooksByDate;
	function_mapping["PD"] = &PrintBooksByDepartment;
	function_mapping["PM"] = &PrintAverageBookCosts;
	function_mapping["//"] = &Comment;
	function_mapping[""]   = &Comment;

	// hold inputs
	std::string input;
	std::vector<std::string> tokens;

	while(getline(std::cin, input)) {
		if (input == "") continue;

		tokens = split(input, ' ');

		if(function_mapping.find(tokens[0]) == function_mapping.end()) {
			std::cout << "Bad command: " << tokens[0] << std::endl;
			continue;
		}

		int return_code = function_mapping[tokens[0]](catalog, tokens);

		switch(return_code) {
			case 1:
				std::cout << "Not enough arguments!" << std::endl;
				break;
			case 2:
				std::cout << "Book not yet defined!" << std::endl;
				break;
			case 3:
				std::cout << "Course not yet defined!" << std::endl;
				break;
			case 4: 
				std::cout << "Bad argument!" << std::endl;
				break;
		}
	}

}
