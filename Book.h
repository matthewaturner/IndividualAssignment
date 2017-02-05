#include <iostream>
#include <iomanip>
#include <string>
#include <map>

class Book {
public:
	// constructors
	Book()
	: isbn(), author() {}

	Book(int _isbn, std::string _title);

	// getters
	int getIsbn()           { return isbn; }
	int getEdition()        { return edition; }
	std::string getTitle()  { return title; }
	std::string getAuthor() { return author; }
	std::string getDate()   { return std::to_string(month) + "/" + std::to_string(year); }

	// setters
	void setTitle(std::string _title)   { title = _title; }
	void setIsbn(int _isbn)             { isbn = _isbn; }
	void setAuthor(std::string _author) { author = _author; }
	void setEdition(int _edition)       { edition = _edition; }
	void setDate(int _month, int _year) { month = _month; year = _year; }
	void setCost(std::string _format, double _cost);

	// other functions
	void print(std::ostream& os);
private:
	std::string title, author;            // title and author
	int isbn, edition, month, year;       // isbn, edition, publish date info
	std::map<std::string, double> prices; // store prices by format e.g. "new"
};
