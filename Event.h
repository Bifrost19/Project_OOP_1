#ifndef EVENT_H
#define EVENT_H
#include "Hall.h"
#include "Date.h"
#include "Reservation.h"
#include "BoughtSeat.h"
#include <iostream>

class Event
{
private:
	Date date;
	char* name;
	Hall hall;
	Reservation* reservations;
	unsigned int reservationCount;
	BoughtSeat* boughtSeats;
	unsigned int boughtSeatCount;

public:
	//Constructors && Destructor
	Event();

	Event(Date date, const char* name, Hall hall);

	~Event();

	//Getters
	Date getDate() const { return this->date; }

	const char* getName() const { return this->name; }

	Hall getHall() const { return this->hall; }

	Reservation* getReservations() const { return this->reservations; }

	unsigned int getReservationCount() const { return this->reservationCount; }

	BoughtSeat* getBoughtSeats() const { return this->boughtSeats; }

	unsigned int getBoughtSeatCount() const { return this->boughtSeatCount; }

	//Setters

	void setReservations(Reservation* reservations, unsigned int reservationCount);

	void setReservationCount(unsigned int reservationCount) { this->reservationCount = reservationCount; }

	void setBoughtSeatCount(unsigned int boughtSeatCount) { this->boughtSeatCount = boughtSeatCount; }

	//Operators

	Event& operator= (const Event& other);

	bool operator== (const Event& other);

	friend std::ostream& operator<< (std::ostream& out, const Event& event);

	//Methods

	void addNewReservation(const Reservation& reservation);

	void removeReservation(const Reservation& reservation);

	void addBoughtSeat(const BoughtSeat& boughtSeat);

};
#endif

