#ifndef BOUGHTSEAT_H
#define BOUGHTSEAT_H
#include <iostream>

class BoughtSeat
{
private:
	unsigned int row;
	unsigned int seat;

public:
	//Constructors
	BoughtSeat();

	BoughtSeat(unsigned int row, unsigned int seat);

	//Getters:
	unsigned int getRow() const { return this->row; }

	unsigned int getSeat() const { return this->seat; }

	//Operators:

	bool operator== (const BoughtSeat& other);

	friend std::ostream& operator<< (std::ostream& out, const BoughtSeat& boughtSeat);
};
#endif

