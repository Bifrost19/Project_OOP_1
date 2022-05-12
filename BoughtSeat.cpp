#include "BoughtSeat.h"
#include <iostream>

BoughtSeat::BoughtSeat()
{
	this->row = 0;
	this->seat = 0;
}

BoughtSeat::BoughtSeat(unsigned int row, unsigned int seat)
{
	this->row = row;
	this->seat = seat;
}

bool BoughtSeat::operator== (const BoughtSeat& other)
{
	return (this->row == other.row && this->seat == other.seat);
}

std::ostream& operator<< (std::ostream& out, const BoughtSeat& boughtSeat)
{
	out << boughtSeat.row << "|" << boughtSeat.seat;
	return out;
}
