#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "Catalog.h"

typedef void (*functionPointer)(std::string);
typedef std::map<std::string, functionPointer> func_map;

/* ----- Splitting input strings into vectors ------------------------------- */

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

std::string combine(const std::vector<std::string>, 
		    std::vector<std::string>::iterator begin,
		    std::vector<std::string>::iterator end) {

	std::string result;
	for(std::vector<std::string>::iterator it = begin; it != end; it++) {
		result += " " + *it;
	}
	return result;
}

/* ----- Functions to work with books --------------------------------------- */

void DefineBook(std::string args) {
	std::cout << args;
}

void DefineCharacteristic(std::string args) {

}

//decltype int getline(std::cin, input, " ") gettoken;

int main() {
	Catalog catalog;
	std::string input;

	while(getline(std::cin, input, ' ')) {
		std::string isbn, option, value, value2, value3;
		input += " ";


		switch(input[0]) {
			case 'B':
				getline(std::cin, isbn, ' ');
				getline(std::cin, value);

				catalog.defineBook(stoi(isbn), value);
				break;
			case 'D':
				getline(std::cin, isbn, ' ');
				getline(std::cin, option, ' ');
				getline(std::cin, value);

				switch(option[0]) {
					case 'A':
						getline(std::cin, value);
						catalog.defineBookAuthor(stoi(isbn), value);
						break;
					case 'E':
						getline(std::cin, value);
						catalog.defineBookEdition(stoi(isbn), stoi(value));
						break;
					case 'D':
						getline(std::cin, value, '/');
						getline(std::cin, value2);
						catalog.defineBookDate(stoi(isbn), stoi(value), stoi(value2));
						break;
					default:
						std::cout << "Bad option for D command: " << option[0] << std::endl;
						getline(std::cin, input);
				}

				break;
			case 'P':
				switch(input[1]) {
					case 'B':
						std::cout << "All books defined: " << std::endl;
						std::cout << catalog.printAllBooks() << std::endl;
						break;
					
					default:
						std::cout << "Bad command: " << input[0] << input[1] << std::endl;
				}
				break;
			default:
				std::cout << "Bad command: " << input[0] << std::endl;
		}
		getline(std::cin, input);
	}

	/*
	func_map function_mapping;
	function_mapping["b"] = &DefineBook;

	function_mapping["b"]("test");
	*/
}
