#include <string>
#include <ctime>

class Book {
public:
	// constructor
	Book(std::string _isbn, std::string _author) 
	: isbn(_isbn), author(_author) {}

	// getters and setters
	std::string getTitle() { return title; }
	std::string getIsbn() { return isbn; }
	std::string getAuthor() { return author; }
	int getEdition() { return edition; }
	std::string getDate() { return std::to_string(date_month) + "/" + std::to_string(date_year); }
	
	// custom destructor does not need to be defined because we use standard types
private:
	std::string title, isbn, author;
	int edition;
	int date_month, date_year;
	int cost_new, cost_used, cost_rented, cost_electronic;
};
