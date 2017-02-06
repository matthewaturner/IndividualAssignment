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
/* Create a new book and add it to the catalog */
	if(args.size() < 3) return 1;

	return catalog.defineBook(stoi(args[1]), combine(args, 2, args.size()));
}

int DefineBookCharacteristic(Catalog& catalog, std::vector<std::string> args) {
/* Give additional information about a book that has been created */
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
			std::vector<std::string> datetokens = split(args[3], '/');
			rcode = catalog.defineBookDate(stoi(args[1]), stoi(datetokens[0]), 
					stoi(datetokens[1]));
			return (rcode) ? 2 : 0;
	}
}

int DefineBookCost(Catalog& catalog, std::vector<std::string> args) { 
/* Set the cost of a book (different for different formats) */
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
			return 5;
	}
}

int PrintBook(Catalog& catalog, std::vector<std::string> args) { 
/* Print all information known about a specific book */
	if(args.size() < 2) return 1;

	return (catalog.printBook(stoi(args[1]), std::cout)) ? 2 : 0;
}

int PrintAllBooks(Catalog& catalog, std::vector<std::string> args) { 
/* Print all information about all known books */
	catalog.printAllBooks(std::cout);
	return 0;
}

int PrintBooksByDepartment(Catalog& catalog, std::vector<std::string> args) { 
/* Print all books which belong to a course with a certain department code */
	if(args.size() < 2) return 1;
	
	int rcode;
	rcode = catalog.printBooksByDepartment(args[1], std::cout);

	return rcode;
}

int PrintBooksByCourse(Catalog& catalog, std::vector<std::string> args) { 
/* Print all books in all sections of a given course */ 
	if(args.size() < 3) return 1;

	int rcode;
	rcode = catalog.printBooksByCourse(args[1], stoi(args[2]), std::cout);

	return (rcode) ? 3 : 0;

}

int PrintBooksBySection(Catalog& catalog, std::vector<std::string> args) { 
/* Print all books required by a given section */
	if(args.size() < 4) return 1;

	int rcode;
	rcode = catalog.printBooksBySection(args[1], stoi(args[2]), stoi(args[3]), std::cout);

	switch(rcode) {
		case 1: return 2;
		case 2: return 4;
	}
}

int PrintBooksByDate(Catalog& catalog, std::vector<std::string> args) {
/* Print all books published on a given date */
	if(args.size() < 2) return 1;

	int rcode;
	rcode = catalog.printBooksByDate(args[1], std::cout);

	return rcode;

}

int PrintAverageBookCosts(Catalog& catalog, std::vector<std::string> args) {
/* Print the average min and max costs for a section in a department */
	if(args.size() < 2) return 1;

	catalog.printAverageBookCosts(args[1], std::cout);

	return 0;
}

int DefineCourse(Catalog& catalog, std::vector<std::string> args) {
/* Create a course and add it to the catalog */
	if(args.size() < 4) return 1;

	catalog.defineCourse(args[1], stoi(args[2]), combine(args, 3, args.size()));
	return 0;
}

int PrintCourses(Catalog& catalog, std::vector<std::string> args) { 
/* Print all known courses */
	catalog.printCourses(std::cout);
	return 0;
}

int AssignBook(Catalog& catalog, std::vector<std::string> args) {
/* Assign a book to a section of a given course */
	if(args.size() < 6) return 1;

	int rcode;
	switch(args[5][0]) {
		case 'R':
			rcode = catalog.assignBook(stoi(args[1]), args[2], stoi(args[3]), stoi(args[4]), 0);
			break;
		case 'O':
			rcode = catalog.assignBook(stoi(args[1]), args[2], stoi(args[3]), stoi(args[4]), 1);
			break;
	}
	
	switch(rcode) {
		case 1: return 3;
		case 2: return 4;
		default: return 0;
	}
}

int Comment(Catalog& catalog, std::vector<std::string> args) {
/* Lets us have command commands, which just print to the console */
	std::cout << " // " << combine(args, 1, args.size()) << std::endl;
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
				std::cout << "Section not yet defined!" << std::endl;
				break;
			case 5: 
				std::cout << "Bad argument!" << std::endl;
				break;
		}
	}

}
