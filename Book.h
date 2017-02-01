#include <string>
#include <ctime>

class Book {
public:
	// constructor
	Book(std::string _isbn, std::string _author) 
	: isbn(_isbn), author(_author) {}

	// getters
	std::string getTitle()  { return title; }
	std::string getIsbn()   { return isbn; }
	std::string getAuthor() { return author; }
	int getEdition()        { return edition; }
	std::string getDate()   { return std::to_string(month) + "/" + std::to_string(year); }

	// setters
	void setTitle(std::string _title)            { title = _title; }
	void setIsbn(std::string _isbn)              { isbn = _isbn; }
	void setAuthor(std::string _author)          { author = _author; }
	void setEdition(int _edition)                { edition = _edition; }
	void setDate(int _month, int _year)          { month = _month; year = _year; }
	void setCostNew(int _cost_new)               { cost_new = _cost_new; }
	void setCostUsed(int _cost_used)             { cost_used = _cost_used; }
	void setCostRented(int _cost_rented)         { cost_rented = _cost_rented; }
	void setCostElectronic(int _cost_electronic) { cost_electronic = _cost_electronic; }
	
	// custom destructor does not need to be defined because we use standard types
private:
	std::string title, isbn, author;
	int edition;
	int month, year;
	int cost_new, cost_used, cost_rented, cost_electronic;
};
