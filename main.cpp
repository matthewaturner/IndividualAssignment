#include <iostream>
#include <string>
#include <map>

typedef void (*functionPointer)(std::string);
typedef std::map<std::string, functionPointer> func_map;

/* ----- Functions to work with books -------------------------------------- */

void DefineBook(std::string args) {
	std::cout << args;
}

void DefineCharacteristic(std::string args) {

}

int main() {
	func_map function_mapping;
	function_mapping["b"] = &DefineBook;

	function_mapping["b"]("test");
}
