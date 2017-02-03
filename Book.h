#include <string>
#include <map>

class Book {
public:
	// constructors
	Book()
	: isbn(), author() {}

	Book(int _isbn, std::string _title) 
	: isbn(_isbn), title(_title) {}

	// getters
	int getIsbn()           { return isbn; }
	int getEdition()        { return edition; }
	std::string getTitle()  { return title; }
	std::string getAuthor() { return author; }
	std::string getDate()   { return std::to_string(month) + "/" + std::to_string(year); }
	std::string print()     { return std::to_string(isbn) + " " + title + " by " + author + "\n"
				         + " Edition " + std::to_string(edition) + " " + getDate(); }

	// setters
	void setTitle(std::string _title)    { title = _title; }
	void setIsbn(int _isbn)              { isbn = _isbn; }
	void setAuthor(std::string _author)  { author = _author; }
	void setEdition(int _edition)        { edition = _edition; }
	void setDate(int _month, int _year)  { month = _month; year = _year; }
	void setCost(std::string _format, double _cost);

	// operator overloading
	std::ostream& operator<< (std::ostream& stream);
	
	// custom destructor does not need to be defined because we use standard types
private:
	int isbn;
	std::string title, author;
	int edition;
	int month, year;
	std::map<std::string, double> prices;
};
