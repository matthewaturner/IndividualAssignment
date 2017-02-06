#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

struct Cost {
	std::string format;
	double cost;
};

class Book {
public:
	// constructors
	Book()
	: isbn(), author() {}

	Book(int _isbn, std::string _title);

	// getters
	int getIsbn()           const { return isbn; }
	int getEdition()        const { return edition; }
	std::string getTitle()  const { return title; }
	std::string getAuthor() const { return author; }
	std::string getDate()   const { return date; }

	// setters
	void setTitle(std::string _title)   { title = _title; }
	void setIsbn(int _isbn)             { isbn = _isbn; }
	void setAuthor(std::string _author) { author = _author; }
	void setEdition(int _edition)       { edition = _edition; }
	void setDate(int _month, int _year);
	void setCost(std::string _format, double _cost);

	// other functions
	void print(std::ostream& os);
	void printPrices(std::ostream& os);
	int minCost();
	int maxCost();

	// operator overloading
	friend bool operator<(const Book& b1, const Book& b2) 
		{ return b1.getIsbn() < b2.getIsbn(); }

private:
	std::string title, author;            // title and author
	std::string date;                     // publish date (format mm/yyyy)
	int isbn, edition;                    // isbn, edition
	std::vector<Cost> costs;              // store costs (format, price) pairs
};
