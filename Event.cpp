#include "Event.h"
#include <iostream>
#include <cstring>

using std::nothrow;

Event::Event()
{
	this->name = nullptr;
	this->reservations = nullptr;
	this->reservationCount = 0;
	this->boughtSeats = nullptr;
	this->boughtSeatCount = 0;
}

Event::Event(Date date, const char* name, Hall hall)
{
	this->date = date;
	this->name = new (nothrow) char[strlen(name) + 1];
	if (!this->name) throw "Memory problem";

	strcpy_s(this->name, strlen(name) + 1, name);

	this->hall = hall;
}

Event::~Event()
{
	delete[] this->name;
	delete[] this->reservations;
}

Event& Event::operator= (const Event& other)
{
	if (this != &other)
	{
		this->date = other.date;
		this->hall = other.hall;

		delete[] this->name;
		this->name = new (nothrow) char[strlen(other.name) + 1];
		if (!this->name) throw "Memory problem!";

		strcpy_s(this->name, strlen(other.name) + 1, other.name);

		this->reservationCount = other.reservationCount;
		delete[] this->reservations;

		this->reservations = new (nothrow) Reservation[this->reservationCount];
		if (!this->reservations) throw "Memory problem";

		for (int i = 0; i < this->reservationCount; i++)
		{
			this->reservations[i] = other.reservations[i];
		}

		this->boughtSeatCount = other.boughtSeatCount;
		delete[] this->boughtSeats;

		this->boughtSeats = new (nothrow) BoughtSeat[this->boughtSeatCount];
		if (!this->boughtSeats) throw "Memory problem";

		for (int i = 0; i < this->boughtSeatCount; i++)
		{
			this->boughtSeats[i] = other.boughtSeats[i];
		}

	}
	return *this;
}

bool Event::operator== (const Event& other)
{
	return (this->date == other.date && this->hall.getNumber() == other.hall.getNumber());
}

std::ostream& operator<< (std::ostream& out, const Event& event)
{
	out << event.name << " * " << event.date << " * " << event.hall;
	return out;
}

void Event::setReservations(Reservation* reservations, unsigned int reservationCount)
{
	this->reservationCount = reservationCount;
	this->reservations = new (nothrow) Reservation[this->reservationCount];
	if (!this->reservations) throw "Memory problem!";

	for (size_t i = 0; i < this->reservationCount; i++)
	{
		this->reservations[i] = reservations[i];
	}
}

void Event::addNewReservation(const Reservation& reservation)
{
	
	Reservation* buffer = new (nothrow) Reservation[this->reservationCount];
	if (!buffer) throw "Memory problem!";

	for (int i = 0; i < this->reservationCount; i++)
	{
		buffer[i] = this->reservations[i];
	}

	this->reservations = new (nothrow) Reservation[this->reservationCount + 1];
	if (!this->reservations) throw "Memory problem!";

	for (int i = 0; i < this->reservationCount; i++)
	{
		this->reservations[i] = buffer[i];
	}
	
	this->reservations[this->reservationCount] = reservation;
	this->reservationCount++;

	delete[] buffer;
}

void Event::removeReservation(const Reservation& reservation)
{
	Reservation* buffer = new (nothrow) Reservation[this->reservationCount];
	if (!buffer) throw "Memory problem!";

	bool isReseravtionPassed = 0;

	for (int i = 0; i < this->reservationCount; i++)
	{
		if (!(this->reservations[i] == reservation))
		{
			buffer[i - isReseravtionPassed] = this->reservations[i];
		}
		else isReseravtionPassed = 1;
	}
	
	this->reservationCount--;
	this->reservations = new (nothrow) Reservation[this->reservationCount];
	if (!this->reservations) throw "Memory problem!";

	for (int i = 0; i < this->reservationCount; i++)
	{
		this->reservations[i] = buffer[i];
	}

	delete[] buffer;
}

void Event::addBoughtSeat(const BoughtSeat& boughtSeat)
{
	BoughtSeat* buffer = new (nothrow) BoughtSeat[this->boughtSeatCount];
	if (!buffer) throw "Memory problem!";

	for (int i = 0; i < this->boughtSeatCount; i++)
	{
		buffer[i] = this->boughtSeats[i];
	}

	this->boughtSeats = new (nothrow) BoughtSeat[this->boughtSeatCount + 1];
	if (!this->boughtSeats) throw "Memory problem!";

	for (int i = 0; i < this->boughtSeatCount; i++)
	{
		this->boughtSeats[i] = buffer[i];
	}

	this->boughtSeats[this->boughtSeatCount] = boughtSeat;
	this->boughtSeatCount++;

	delete[] buffer;
}
