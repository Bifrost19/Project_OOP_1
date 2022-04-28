#ifndef DATE_H
#define DATE_H
#include <iostream>

class Date
{
private:
	unsigned int year;
	unsigned int month;
	unsigned int day;

public:
	//Constructors
	Date();

	Date(unsigned int year, unsigned int month, unsigned int day);

	//Getters
	unsigned int getYear() const { return this->year; }

	unsigned int getMonth() const { return this->month; }

	unsigned int getDay() const { return this->day; }

	//Operators
	Date& operator= (const Date& other);

	bool operator== (const Date& other);

	bool operator> (const Date& other);

	bool operator< (const Date& other);

	friend std::istream& operator>> (std::istream& in, Date& date);

	friend std::ostream& operator<< (std::ostream& out, const Date& date);
};
#endif
