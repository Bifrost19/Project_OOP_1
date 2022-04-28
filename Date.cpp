#include "Date.h"
#include <iostream>
#include <cassert>

Date::Date()
{
	this->year = 0;
	this->month = 0;
	this->day = 0;
}

bool isYearLeap(unsigned int year)
{
	if ((year % 4 == 0 || year % 100) && year % 400 != 0) return true;
	else return false;
}

bool verifyDate(unsigned int year, unsigned int month, unsigned int day)
{
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		return (day >= 1 && day <= 31);
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		return (day >= 1 && day <= 30);
	}
	else if (isYearLeap(year) && month == 2)
	{
		return (day >= 1 && day <= 29);
	}
	else if (!isYearLeap(year) && month == 2)
	{
		return (day >= 1 && day <= 28);
	}

}

Date::Date(unsigned int year, unsigned int month, unsigned int day)
{
	assert(year > 0);
	this->year = year;
	assert(month >= 1 && month <= 12);
	this->month = month;
	assert(verifyDate(year, month, day));
	this->day = day;
}

Date& Date::operator= (const Date& other)
{
	if (this != &other)
	{
		this->year = other.year;
		this->month = other.month;
		this->day = other.day;
	}
	return *this;
}

bool Date::operator== (const Date& other)
{
	return (this->year == other.year && this->month == other.month && this->day == other.day);
}

bool Date::operator> (const Date& other)
{
	if (this->year != other.year) return this->year > other.year;
	else if (this->month != other.month) return this->month > other.month;
	else return this->day > other.day;
}

bool Date::operator< (const Date& other)
{
	return !(*this > other || *this == other);
}

std::istream& operator>> (std::istream& in, Date& date)
{
	do
	{
		in >> date.year;
	} while (date.year <= 0);
	do
	{
		in >> date.month;
	} while (date.month < 1 || date.month > 12);
	do
	{
		in >> date.day;
	} while (!verifyDate(date.year, date.month, date.day));

	return in;
}

std::ostream& operator<< (std::ostream& out, const Date& date)
{
	out << date.year << "/" << date.month << "/" << date.day;
	return out;
}
