#include "Book.h"

Book::Book(int _isbn, std::string _title) {
	isbn = _isbn;
	title = _title;
	author = "unknown";
	edition = 1;
	date = "00/0000";
}

void Book::setDate(int _month, int _year) {
	date = "";
	if(_month < 10)
		date += "0";
	date += std::to_string(_month) + "/" + std::to_string(_year);
}

void Book::setCost(std::string _format, double _cost) {
	bool found = false;
	for(Cost& c : costs) {
		if (c.format == _format) {
			c.cost = _cost;
			return;
		}
	}

	costs.push_back(Cost{_format, _cost});
}

void Book::print(std::ostream& os) {
	// print book itself
	os << isbn << " " << title << " (Edition " << edition << ") by "
	   << author << ", Published " << getDate() << std::endl;
	// set precision of double values
	os << std::setprecision(2) << std::fixed;
}

void Book::printPrices(std::ostream& os) {
	// print book prices
	for(Cost& c : costs) {
		os << c.format << "=" << c.cost << " ";
	}
}

int Book::minCost() {
	int min_cost;

	if(costs.size() > 0)
		min_cost = costs[0].cost;
	else
		return -1;

	for(int i=1; i<costs.size(); i++) {
		if(costs[i].cost < min_cost)
			min_cost = costs[i].cost;
	}
	return min_cost;
}

int Book::maxCost() {
	int max_cost;

	if(costs.size() > 0)
		max_cost = costs[0].cost;
	else
		return -1;

	for(int i=1; i<costs.size(); i++) {
		if(costs[i].cost > max_cost)
			max_cost = costs[i].cost;
	}

	return max_cost;
}
