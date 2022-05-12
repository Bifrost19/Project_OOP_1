#ifndef HALL_H
#define HALL_H
#include <iostream>

class Hall
{
private:
	unsigned int number;
	unsigned int rowCount;
	unsigned int seatCountInRow;
	
public:
	//Constructors
	Hall();

	Hall(unsigned int number, unsigned int rowCount, unsigned int seatCountInRow);

	//Getters
	unsigned int getNumber() const { return this->number; }

	unsigned int getRowCount() const { return this->rowCount; }

	unsigned int getSeatCountInRow() const { return this->seatCountInRow; }

	//Setters

	void setNumber(unsigned int number) { this->number = number; }

	void setRowCount(unsigned int rowCount) { this->rowCount = rowCount; }

	void setSeatCountInRow(unsigned int seatCountInRow) { this->seatCountInRow = seatCountInRow; }

	//Operators
	Hall& operator= (const Hall& other);

	bool operator== (const Hall& other);

	friend std::istream& operator>> (std::istream& in, Hall& hall);

	friend std::ostream& operator<< (std::ostream& out, const Hall& hall);
};
#endif
