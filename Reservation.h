#ifndef RESERVATION_H
#define RESERVATION_H
#include <iostream>

class Reservation
{
private:
	unsigned int row;
	unsigned int seat;
	char* password;
	char* note; //optional

public:
	//Constructors & Destructor
	Reservation();

	Reservation(unsigned int row, unsigned int seat, const char* password);

	Reservation(unsigned int row, unsigned int seat, const char* password, const char* note); //Constructs with note

	~Reservation();

	//Getters
	unsigned int getRow() const { return this->row; }

	unsigned int getSeat() const { return this->seat; }

	const char* getPassword() const { return this->password; }

	const char* getNote() const { return this->note; }

	//Operators

	Reservation& operator= (const Reservation& other);

	bool operator== (const Reservation& other);

	friend std::ostream& operator<< (std::ostream& out, const Reservation& reservation);
};
#endif
