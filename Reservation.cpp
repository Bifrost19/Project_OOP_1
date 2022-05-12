#include "Reservation.h"
#include <iostream>
#include <cassert>

using std::nothrow;

Reservation::Reservation()
{
	this->row = 0;
	this->seat = 0;
	this->password = nullptr;
	this->note = nullptr;
}

Reservation::Reservation(unsigned int row, unsigned int seat, const char* password)
{
	assert(row > 0);
	this->row = row;
	assert(seat > 0);
	this->seat = seat;

	this->password = new (nothrow) char[strlen(password) + 1];
	if (!this->password) throw "Memory problem!";
	
	strcpy_s(this->password, strlen(password) + 1, password);
	this->note = nullptr;
}

Reservation::Reservation(unsigned int row, unsigned int seat, const char* password, const char* note)
{
	assert(row > 0);
	this->row = row;
	assert(seat > 0);
	this->seat = seat;

	this->password = new (nothrow) char[strlen(password) + 1];
	if (!this->password) throw "Memory problem!";
	strcpy_s(this->password, strlen(password) + 1, password);

	this->note = new (nothrow) char[strlen(note) + 1];
	if (!this->note) throw "Memory problem!";
	strcpy_s(this->note, strlen(note) + 1, note);
}

Reservation::~Reservation()
{
	delete[] this->password;
	delete[] this->note;
}

Reservation& Reservation::operator= (const Reservation& other)
{
	if (this != &other)
	{
		this->row = other.row;
		this->seat = other.seat;

		delete[] this->password;
		this->password = new (nothrow) char[strlen(other.password) + 1];
		if (!this->password) throw "Memory problem!";

		strcpy_s(this->password, strlen(other.password) + 1, other.password);

		if (other.note == nullptr) this->note = nullptr;
		else
		{
			delete[] this->note;
			this->note = new (nothrow) char[strlen(other.note) + 1];
			if (!this->note) throw "Memory problem!";
			strcpy_s(this->note, strlen(other.note) + 1, other.note);
		}

	}
	return *this;
}

bool Reservation::operator== (const Reservation& other)
{
	return (!strcmp(this->password, other.password) && this->row == other.row && this->seat == other.seat);
}

std::ostream& operator<< (std::ostream& out, const Reservation& reservation)
{
	out << reservation.row << "/" << reservation.seat << "|" << reservation.password << "|" << reservation.note;
	return out;
}
