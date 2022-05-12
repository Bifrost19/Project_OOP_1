#include "Hall.h"
#include <iostream>
#include <cassert>

Hall::Hall()
{
	this->number = 0;
	this->rowCount = 0;
	this->seatCountInRow = 0;
}

Hall::Hall(unsigned int number, unsigned int rowCount, unsigned int seatCountInRow)
{
	assert(number > 0);
	this->number = number;
	assert(rowCount > 0);
	this->rowCount = rowCount;
	assert(seatCountInRow > 0);
	this->seatCountInRow = seatCountInRow;
}

Hall& Hall::operator= (const Hall& other)
{
	if (this != &other)
	{
		this->number = other.number;
		this->rowCount = other.rowCount;
		this->seatCountInRow = other.seatCountInRow;
	}
	return *this;
}

bool Hall::operator== (const Hall& other)
{
	return (this->number == other.number && this->rowCount == other.rowCount && this->seatCountInRow == other.seatCountInRow);
}

std::istream& operator>> (std::istream& in, Hall& hall)
{
	do
	{
		in >> hall.number;
	} while (hall.number <= 0);
	do
	{
		in >> hall.rowCount;
	} while (hall.rowCount <= 0);
	do
	{
		in >> hall.seatCountInRow;
	} while (hall.seatCountInRow <= 0);

	return in;
}

std::ostream& operator<< (std::ostream& out, const Hall& hall)
{
	out << hall.number << "|" << hall.rowCount << "|" << hall.seatCountInRow << "|";
	return out;
}
