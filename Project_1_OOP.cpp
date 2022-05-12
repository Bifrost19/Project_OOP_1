#include <iostream>
#include <fstream>
#include "Event.h"

using namespace std;

//Global variables
Hall* halls = nullptr;
unsigned int hallCount = 0;
Event* events = nullptr;
unsigned int eventCount = 0;

void defineHalls()
{
	//Halls:
	hallCount = 5;

	Hall hall1 = Hall(1, 15, 30);
	Hall hall2 = Hall(2, 20, 35);
	Hall hall3 = Hall(3, 25, 40);
	Hall hall4 = Hall(4, 40, 50);
	Hall hall5 = Hall(5, 70, 60);

	halls = new (nothrow) Hall[hallCount];
	if (!halls) throw "Memory problem";

	halls[0] = hall1;
	halls[1] = hall2;
	halls[2] = hall3;
	halls[3] = hall4;
	halls[4] = hall5;
}

void freeHeapMemory()
{
	// Delete all dynamically allocated global variables
	delete[] halls;
	delete[] events;
}

//Convertation functions
unsigned int toInt(char string[])
{
	int stringLength = strlen(string);
	unsigned int num = 0;

	for (int i = 0; i < stringLength; i++)
	{
		num += (string[i] - '0') * pow(10, stringLength - i - 1);
	}

	return num;
}

char* toString(unsigned int num)
{
	int iterator = 0;
	int numCopy = num;
	int numLength = 0;

	while (numCopy > 0)
	{
		numCopy /= 10;
		numLength++;
	}

	char* numStr = new (nothrow) char[numLength + 1];
	if (!numStr) throw "Memory problem!";

	while (num > 0)
	{
		numStr[iterator++] = (num % 10) + '0';
		num /= 10;
	}

	numStr[iterator] = '\0';
	_strrev(numStr);
	return numStr;
}

Date convertFromStringToDate(char dateStr[])
{
	int dateStrLength = strlen(dateStr);

	int intervalCounter = 0;
	int iterator = 0;
	char partialDateStr[10];

	unsigned int year = 0;
	unsigned int month = 0;
	unsigned int day = 0;

	for (int i = 0; i < dateStrLength; i++)
	{
		switch (intervalCounter)
		{
		case 0:
			if (dateStr[i] == ' ')
			{
				partialDateStr[iterator] = '\0';
				year = toInt(partialDateStr);
				strcpy_s(partialDateStr, "");
				intervalCounter++;
				iterator = 0;
			}
			else partialDateStr[iterator++] = dateStr[i];
			break;

		case 1:
			if (dateStr[i] == ' ')
			{
				partialDateStr[iterator] = '\0';
				month = toInt(partialDateStr);
				strcpy_s(partialDateStr, "");
				intervalCounter++;
				iterator = 0;
			}
			else partialDateStr[iterator++] = dateStr[i];
			break;

		case 2:
			if (i == dateStrLength - 1)
			{
				partialDateStr[iterator++] = dateStr[i];
				partialDateStr[iterator] = '\0';
				day = toInt(partialDateStr);
			}
			else partialDateStr[iterator++] = dateStr[i];
			break;
		}
	}

	return Date(year, month, day);
}

char* convertFromDateToString(Date date)
{
	char dateStr[50];

	strcpy_s(dateStr, toString(date.getYear()));
	strcat_s(dateStr, " ");
	strcat_s(dateStr, toString(date.getMonth()));
	strcat_s(dateStr, " ");
	strcat_s(dateStr, toString(date.getDay()));

	char* dateStrP = new (nothrow) char[strlen(dateStr) + 1];
	if (!dateStrP) throw "Memory problem!";
	strcpy_s(dateStrP, strlen(dateStr) + 1, dateStr);
	return dateStrP;
}

//Save & Load Halls & Events from files
void saveEventsToFile()
{
	ofstream eventWFile("events.txt");
	if (!eventWFile.is_open()) throw "The file can't be opened!";

	eventWFile << eventCount << endl;
	eventWFile << "--------------------------------------------" << endl;
	int eventIterator = 0;

	while (eventIterator < eventCount)
	{
		eventWFile << events[eventIterator].getDate() << endl;
		eventWFile << events[eventIterator].getName() << endl;
		eventWFile << events[eventIterator].getHall() << endl;

		eventWFile << events[eventIterator].getReservationCount() << endl;
		unsigned int reservationCount = events[eventIterator].getReservationCount();
		for (int i = 0; i < reservationCount; i++)
		{
			eventWFile << events[eventIterator].getReservations()[i] << endl;
		}

		eventWFile << events[eventIterator].getBoughtSeatCount() << endl;
		unsigned int boughtSeatCount = events[eventIterator].getBoughtSeatCount();
		for (int i = 0; i < boughtSeatCount; i++)
		{
			eventWFile << events[eventIterator].getBoughtSeats()[i] << endl;
		}
		eventWFile << "--------------------------------------------" << endl;
		eventIterator++;
	}
	eventWFile.close();
}

void readEventsFromFile()
{
	ifstream eventRFile("events.txt");
	if (!eventRFile.is_open()) throw "The file can't be opened!";

	eventRFile >> eventCount;

	events = new (nothrow) Event[eventCount];
	if (!events) throw "Memory prblem!";

	int eventIterator = 0;

	eventRFile.ignore();
	char array[100];
	eventRFile.getline(array, 100, '\n');
	strcpy_s(array, "");

	unsigned int invalidEventCount = 0;

	while (eventIterator < eventCount)
	{
		//Date
		eventRFile.getline(array, 10, '/');
		unsigned int year = toInt(array);
		strcpy_s(array, "");

		eventRFile.getline(array, 10, '/');
		unsigned int month = toInt(array);
		strcpy_s(array, "");

		eventRFile.getline(array, 10, '\n');
		unsigned int day = toInt(array);
		strcpy_s(array, "");

		//Name
		eventRFile.getline(array, 100, '\n');
		char* name = new (nothrow) char[strlen(array) + 1];
		if (!name) throw "Memory problem!";
		strcpy_s(name, strlen(array) + 1, array);
		strcpy_s(array, "");

		//Hall
		Hall hall;

		eventRFile.getline(array, 10, '|');
		hall.setNumber(toInt(array));
		strcpy_s(array, "");

		eventRFile.getline(array, 10, '|');
		hall.setRowCount(toInt(array));
		strcpy_s(array, "");

		eventRFile.getline(array, 10, '|');
		hall.setSeatCountInRow(toInt(array));
		strcpy_s(array, "");

		Event event = Event(Date(year, month, day), name, hall);

		//Reservations
		unsigned int reservationCount;
		eventRFile >> reservationCount;
		eventRFile.ignore();

		for (int i = 0; i < reservationCount; i++)
		{
			//Row
			eventRFile.getline(array, 10, '/');
			unsigned int row = toInt(array);
			strcpy_s(array, "");

			//Seat
			eventRFile.getline(array, 10, '|');
			unsigned int seat = toInt(array);
			strcpy_s(array, "");

			//Password
			eventRFile.getline(array, 100, '|');
			char* password = new (nothrow) char[strlen(array) + 1];
			if (!password) throw "Memory problem!";
			strcpy_s(password, strlen(array) + 1, array);
			strcpy_s(array, "");

			//Note
			eventRFile.getline(array, 100, '\n');
			char* note = new (nothrow) char[strlen(array) + 1];
			if (!note) throw "Memory problem!";
			strcpy_s(note, strlen(array) + 1, array);
			strcpy_s(array, "");

			Reservation reservation = Reservation(row, seat, password, note);
			//Check if there is same reservation
			bool isThereSameReservation = false;

			for (int j = 0; j < i; j++)
			{
				if (reservation.getRow() == event.getReservations()[j].getRow() &&
					reservation.getSeat() == event.getReservations()[j].getSeat())
				{
					isThereSameReservation = true;
					break;
				}
			}

			if(!isThereSameReservation)
			event.addNewReservation(reservation);
		}

		//Bought seats
		unsigned int boughtSeatCount;
		eventRFile >> boughtSeatCount;
		eventRFile.ignore();

		for (int i = 0; i < boughtSeatCount; i++)
		{
			//Row
			eventRFile.getline(array, 10, '|');
			unsigned int row = toInt(array);
			strcpy_s(array, "");

			//Seat
			eventRFile.getline(array, 10, '\n');
			unsigned int seat = toInt(array);
			strcpy_s(array, "");

			BoughtSeat boughtSeat = BoughtSeat(row, seat);

			//Check if there is same bought seat
			bool isThereSameBoughtSeat = false;

			for (int j = 0; j < i; j++)
			{
				if (boughtSeat.getRow() == event.getBoughtSeats()[j].getRow() &&
					boughtSeat.getSeat() == event.getBoughtSeats()[j].getSeat())
				{
					isThereSameBoughtSeat = true;
					break;
				}
			}

			if (!isThereSameBoughtSeat)
				event.addBoughtSeat(boughtSeat);
		}

		eventRFile.getline(array, 100, '\n');
		strcpy_s(array, "");

		//Check if there is event with the same parameters
		bool isThereSameEvent = false;

		for (int i = 0; i < eventIterator; i++)
		{
			if (events[i].getDate() == event.getDate() && events[i].getHall() == event.getHall())
			{
				isThereSameEvent = true;
				invalidEventCount++;
				break;
			}
		}

		if (!isThereSameEvent)
		events[eventIterator - invalidEventCount] = event;

		eventIterator++;
	}

	eventCount -= invalidEventCount;
	eventRFile.close();
}

void saveHallsToFile()
{
	ofstream hallsWFile("halls.txt");
	if (!hallsWFile.is_open()) throw "The file can't be opened";

	//Saving the halls
	int hallsIterator = 0;

	hallsWFile << hallCount << endl;

	while (hallsIterator < hallCount)
	{
		hallsWFile << halls[hallsIterator++] << endl;
	}

	hallsWFile.close();
}

void readHallsFromFile()
{
	ifstream hallsRFile("halls.txt");
	if (!hallsRFile.is_open()) throw "The file can't be opened";

	//Reading halls
	hallsRFile >> hallCount;
	halls = new (nothrow) Hall[hallCount];
	if (!halls) throw "Memory problem!";
	unsigned int hallsIterator = 0;
	unsigned int invalidHallCount = 0;
	
	while (hallsIterator < hallCount)
	{
		char array[10];
		//Number
		hallsRFile.ignore().getline(array, 10,'|');
		unsigned int number = toInt(array);
		strcpy_s(array, "");

		//RowCount
		hallsRFile.getline(array, 10, '|');
		unsigned int rowCount = toInt(array);
		strcpy_s(array, "");

		//SeatCountInRow
		hallsRFile.getline(array, 10, '|');
		unsigned int seatCountInRow = toInt(array);

		Hall hall = Hall(number, rowCount, seatCountInRow);

		//Check if there is same hall
		bool isThereSameHall = false;

		for (int i = 0; i < hallsIterator; i++)
		{
			if (hall.getNumber() == halls[i].getNumber())
			{
				isThereSameHall = true;
				invalidHallCount++;
				break;
			}
		}

		if (!isThereSameHall)
			halls[hallsIterator] = hall;

		hallsIterator++;
	}

	hallCount -= invalidHallCount;
	hallsRFile.close();
}

void saveAndLoadHallsAndEventsFromFiles()
{
	fstream hallsFile("halls.txt", ios::in);
	if (!hallsFile.is_open())
	{
		defineHalls();
		saveHallsToFile();
	}
	else
	{
		readHallsFromFile();
		hallsFile.close();
	}

	fstream eventFile("events.txt", ios::in);
	if (!eventFile.is_open()) saveEventsToFile();
	else
	{
		readEventsFromFile();
		eventFile.close();
	}
}

//Help functions
void copyEventsInBuffer()
{
	Event* buffer = new (nothrow) Event[eventCount];
	if (!buffer) throw "Memory problem!";

	for (int i = 0; i < eventCount; i++)
	{
		buffer[i] = events[i];
	}

	delete[] events;
	events = new (nothrow) Event[eventCount + 1];
	if (!events) throw "Memory problem!";

	for (int i = 0; i < eventCount; i++)
	{
		events[i] = buffer[i];
	}

	delete[] buffer;
}

bool isThereEventWithSameNameAndDate(const Event& event, const char* name, Date date)
{
	//cout << event.getName() << " " << name << "|" << event.getDate() << " " << date << endl;
	return (!strcmp(event.getName(), name) && event.getDate() == date);
}

int getIndexOfEvent()
{
	char name[100];
	Date date;
	int eventIndex = -1;

	cout << "Enter the name of the event: ";
	cin.getline(name, 100);

	cout << "Enter the date: ";
	cin >> date;
	cin.ignore();

	//Finds the event matching the arguments
	for (int i = 0; i < eventCount; i++)
	{

		if (isThereEventWithSameNameAndDate(events[i], name, date))
		{
			return i;
		}

	}

	return -1; //If there are not events with these parameters
}

Reservation createReservation(Event* events, unsigned int eventIndex)
{
	unsigned int row;
	unsigned int seat;
	char password[100];

	//Three inputs for reservation

	cout << "Enter row: ";
	do
	{
		cin >> row;
	} while (row < 0 && row > events[eventIndex].getHall().getRowCount());

	cout << "Enter seat: ";
	do
	{
		cin >> seat;
	} while (seat < 0 && seat > events[eventIndex].getHall().getSeatCountInRow());

	cout << "Enter the password: ";
	cin.ignore().getline(password, 100);


	//Add reservation to reservations of the event
	return Reservation(row, seat, password);
}

bool isThereExistingReservationWithRowAndSeat(unsigned int eventIndex, const Reservation& reservation)
{
	for (int i = 0; i < events[eventIndex].getReservationCount(); i++)
	{
		if (events[eventIndex].getReservations()[i].getRow() == reservation.getRow() &&
			events[eventIndex].getReservations()[i].getSeat() == reservation.getSeat())
			return true;
	}
	return false;
}

bool isThereExistingReservation(unsigned int eventIndex, Reservation& reservation)
{
	for (int i = 0; i < events[eventIndex].getReservationCount(); i++)
	{
		if (events[eventIndex].getReservations()[i] == reservation)
		{
			reservation = events[eventIndex].getReservations()[i];
			return true;
		}
	}

	return false;
}

void transformReservationInBoughtSeat(unsigned int eventIndex, const Reservation& reservation, const BoughtSeat& boughtSeat)
{
	char password[100];

	cout << "This seat is reserved! Enter the password for the reservation: ";
	cin.ignore().getline(password, 100);

	if (strcmp(password, reservation.getPassword()))
	{
		cout << "Incorrect password!" << endl;
		return;
	}

	events[eventIndex].removeReservation(reservation);
	events[eventIndex].addBoughtSeat(boughtSeat);
}

//Main functions
void addNewEvent()
{
	cout << endl << "---------Procedure for addition of event-----------------" << endl;
	Date date;
	char name[100];
	unsigned int hallNumber;

	//Three inputs
	cout << "Enter the date: ";
	cin >> date;

	cout << "Enter the name: ";
	cin.ignore().getline(name, 100);

	cout << "Enter the number of the hall: ";
	do
	{
		cin >> hallNumber;
	} while (hallNumber <= 0 || hallNumber > hallCount);

	cin.ignore();

	Hall hall = halls[hallNumber - 1];

	Event event = Event(date, name, hall);

	//Check if there are already existing events
	if (eventCount == 0)
	{	
		events = new (nothrow) Event[eventCount + 1];
		if (!events) throw "Memory problem!";
		events[eventCount] = event;
		eventCount++;
		cout << "The event was added successfully!" << endl;
		saveEventsToFile();
	}
	else
	{
		for (int i = 0; i < eventCount; i++)
		{
			if (events[i] == event)
			{
				cout << "There is another event with these parameters!" << endl;
				return;
			}
		}

		copyEventsInBuffer();
		events[eventCount] = event;
		eventCount++;
		cout << "The event was added successfully!" << endl;
		saveEventsToFile();
	}
}

void reserveTicket()
{
	cout << endl << "---------Procedure for reservation-----------------" << endl;

	int eventIndex = getIndexOfEvent();

	//If there is no such event returns without addition of reservation
	if (eventIndex == -1)
	{
		cout << "There is no such event!";
		return;
	}
	
	Reservation reservation = createReservation(events, eventIndex);

	//Check if the seat is already bought
	for (int i = 0; i < events[eventIndex].getBoughtSeatCount(); i++)
	{
		if (events[eventIndex].getBoughtSeats()[i].getRow() == reservation.getRow()
			&& events[eventIndex].getBoughtSeats()[i].getSeat() == reservation.getSeat())
		{
			cout << "The seat is already bought!" << endl;
			return;
		}
	}

	char note[200];
	cout << "Write a note(optional): ";
	cin.getline(note, 200);

	reservation = Reservation(reservation.getRow(), reservation.getSeat(), reservation.getPassword(), note);

	//Check if there is already a reservation with these parameters
	if (isThereExistingReservationWithRowAndSeat(eventIndex, reservation))
	{
		cout << "There is already such reservation!" << endl;
		return;
	}

	events[eventIndex].addNewReservation(reservation);
	cout << "The reservation was made successfully!" << endl;
	saveEventsToFile();
}

void cancelReservation()
{
	cout << endl << "---------Procedure for cancelation of reservation-----------------" << endl;

	//cin.ignore();

	int eventIndex = getIndexOfEvent();

	//If there is no such event returns without addition of reservation
	if (eventIndex == -1)
	{
		cout << "There is no such event!" << endl;
		return;
	}

	Reservation reservation = createReservation(events, eventIndex);

	//Check if there is already a reservation with these parameters
	if (!isThereExistingReservation(eventIndex, reservation))
	{
		cout << "There is no such reservation or the password is incorrect!" << endl;
		return;
	}

	events[eventIndex].removeReservation(reservation);
	cout << "The reservation was cancelled successfully!" << endl;
	saveEventsToFile();
}

void buyTicket()
{
	cout << endl << "---------Procedure for buying a ticket-----------------" << endl;

	int eventIndex = getIndexOfEvent();

	//If there is no such event returns without addition of reservation
	if (eventIndex == -1)
	{
		cout << "There is no such event!";
		return;
	}

	unsigned int row;
	unsigned int seat;

	cout << "Enter row: ";
	do
	{
		cin >> row;
	} while (row < 0 && row > events[eventIndex].getHall().getRowCount());

	cout << "Enter seat: ";
	do
	{
		cin >> seat;
	} while (seat < 0 && seat > events[eventIndex].getHall().getSeatCountInRow());

	BoughtSeat potentialBoughtSeat = BoughtSeat(row, seat);

	//Check if the seat is already bought
	for (int i = 0; i < events[eventIndex].getBoughtSeatCount(); i++)
	{
		if (events[eventIndex].getBoughtSeats()[i] == potentialBoughtSeat)
		{
			cout << "Sorry! This seat is already bought!" << endl;
			cin.ignore();
			return;
		}
	}

	//Check if the seat is already reserved
	for (int i = 0; i < events[eventIndex].getReservationCount(); i++)
	{
		if (events[eventIndex].getReservations()[i].getRow() == potentialBoughtSeat.getRow()
			&& events[eventIndex].getReservations()[i].getSeat() == potentialBoughtSeat.getSeat())
		{
			transformReservationInBoughtSeat(eventIndex, events[eventIndex].getReservations()[i], potentialBoughtSeat);
			cout << "The ticket was bought successfully!" << endl;
			saveEventsToFile();
			return;
		}
	}

	//If the seat is not bought or reserved, it will be bought and added to bought seats
	events[eventIndex].addBoughtSeat(potentialBoughtSeat);

	cout << "The ticket was bought successfully!" << endl;
	saveEventsToFile();
	cin.ignore();
}

void printFreeSeatsReport()
{
	cout << endl << "---------Report for free seats-----------------" << endl;


	int eventIndex = getIndexOfEvent();

	//If there is no such event returns without addition of reservation
	if (eventIndex == -1)
	{
		cout << "There is no such event!" << endl;
		return;
	}

	unsigned int freeSeatCount = (events[eventIndex].getHall().getRowCount() * events[eventIndex].getHall().getSeatCountInRow())
								  - events[eventIndex].getReservationCount() - events[eventIndex].getBoughtSeatCount();


	char fileName[100] = "report-freeseats-";
	strcat_s(fileName, events[eventIndex].getName());
	strcat_s(fileName, "-");
	strcat_s(fileName, convertFromDateToString(events[eventIndex].getDate()));
	strcat_s(fileName, ".txt");

	ofstream freeSeatsReportFile(fileName);

	if (!freeSeatsReportFile.is_open()) throw "A file with such name can't be opened!";

	freeSeatsReportFile << "*Report for free seats*" << endl;
	freeSeatsReportFile << events[eventIndex].getName() << "|" << convertFromDateToString(events[eventIndex].getDate()) << ":" << endl;
	freeSeatsReportFile << "Count of free seats: " << freeSeatCount << " of " <<
							(events[eventIndex].getHall().getRowCount() * events[eventIndex].getHall().getSeatCountInRow()) << endl;

	freeSeatsReportFile.close();
}

void printReservationReport()
{
	cout << endl << "---------Report for reservations-----------------" << endl;

	char name[100];
	char dateStr[50];
	int eventIndex = -1;

	cout << "Enter the name of the event: ";
	cin.getline(name, 100);

	cout << "Enter the date: ";
	cin.getline(dateStr, 50);

	//Creating the file
	ofstream reservationReport;

	if (!strcmp(dateStr, "ALL"))
	{

		reservationReport.open("report-ALL-ALL.txt");
		if (!reservationReport.is_open()) throw "A file with such name can't be opened!";

		//Writing to the file
		reservationReport << "*Report for reservations*" << endl;
		for (int i = 0; i < eventCount; i++)
		{
			reservationReport << events[i].getName() << "|" << events[i].getDate() << " :" << endl;

			for (int j = 0; j < events[i].getReservationCount(); j++)
			{
				reservationReport << (j + 1) << ". " << "Row: " << events[i].getReservations()[j].getRow() << "|Seat: "
								  << events[i].getReservations()[j].getSeat() << "|Password: "
								  << events[i].getReservations()[j].getPassword() << "|Note: "
								  << events[i].getReservations()[j].getNote() << endl;
			}
			reservationReport << "-----------------------------------" << endl;
		}

		reservationReport.close();
	}
	else
	{
		Date date = convertFromStringToDate(dateStr);

		if (!strcmp(name, "ALL"))
		{
			char fileName[100] = "report-ALL-";
			strcat_s(fileName, dateStr);
			strcat_s(fileName, ".txt");

			reservationReport.open(fileName);
			if (!reservationReport.is_open()) throw "A file with such name can't be opened!";

			reservationReport << "*Report for reservations*" << endl;
			for (int i = 0; i < eventCount; i++)
			{
				if (events[i].getDate() == date)
				{
					reservationReport << events[i].getName() << "|" << events[i].getDate() << " :" << endl;

					for (int j = 0; j < events[i].getReservationCount(); j++)
					{
						reservationReport << (j + 1) << ". " << "Row: " << events[i].getReservations()[j].getRow() << "|Seat: "
							<< events[i].getReservations()[j].getSeat() << "|Password: "
							<< events[i].getReservations()[j].getPassword() << "|Note: "
							<< events[i].getReservations()[j].getNote() << endl;
					}
					reservationReport << "-----------------------------------" << endl;
				}
			}

			reservationReport.close();
		}
		else
		{
			int eventIndex = -1;

			//Finds the event matching the arguments
			for (int i = 0; i < eventCount; i++)
			{

				if (isThereEventWithSameNameAndDate(events[i], name, date))
				{
					eventIndex = i;
				}

			}

			//If there is no such event returns without addition of reservation
			if (eventIndex == -1)
			{
				cout << "There is no such event!" << endl;
				return;
			}

			//Concatenating the name of the file
			char fileName[100] = "report-";
			strcat_s(fileName, name);
			strcat_s(fileName, "-");
			strcat_s(fileName, dateStr);
			strcat_s(fileName, ".txt");

			reservationReport.open(fileName);
			if (!reservationReport.is_open()) throw "A file with such name can't be opened!";
	
			//Writing to the file
			reservationReport << "*Report for reservations*" << endl;
			reservationReport << events[eventIndex].getName() << "|" << events[eventIndex].getDate() << " :" << endl;

			for (int i = 0; i < events[eventIndex].getReservationCount(); i++)
			{
				reservationReport << (i + 1) << ". " << "Row: " << events[eventIndex].getReservations()[i].getRow() << "|Seat: "
					<< events[eventIndex].getReservations()[i].getSeat() << "|Password: "
					<< events[eventIndex].getReservations()[i].getPassword() << "|Note: "
					<< events[eventIndex].getReservations()[i].getNote() << endl;
			}
			reservationReport << "-----------------------------------" << endl;

			reservationReport.close();
		}
	}
}

void printBoughtTicketsReport()
{
	cout << endl << "---------Report for bought tickets in period-----------------" << endl;

	char hallStr[4];
	Date firstDate;
	Date secondDate;

	//Three inputs with verifications
	cout << "Enter the index of the hall: ";
	do
	{
		cin.getline(hallStr, 4);
	} while ((toInt(hallStr) <= 0 || toInt(hallStr) > hallCount) && strcmp(hallStr, "ALL"));

	cout << "Enter the first date: ";
	cin >> firstDate;

	cout << "Enter the second date: ";
	do
	{
		cin >> secondDate;
	} while (firstDate > secondDate);

	cin.ignore();

	//Creating the file
	ofstream boughtTicketsReportFile;

	if (!strcmp(hallStr, "ALL"))
	{
		//Constructing the name of the file
		char fileName[100] = "report-boughttickets-";
		strcat_s(fileName, "ALL-");
		strcat_s(fileName, convertFromDateToString(firstDate));
		strcat_s(fileName, "-");
		strcat_s(fileName, convertFromDateToString(secondDate));
		strcat_s(fileName, ".txt");

		boughtTicketsReportFile.open(fileName);
		if (!boughtTicketsReportFile.is_open()) throw "A file with such name can't be opened!";

		boughtTicketsReportFile << "*Report for bought tickets*" << endl;
		boughtTicketsReportFile << firstDate.getYear() << "/" << firstDate.getMonth() << "/" << firstDate.getDay() << "-"
			<< secondDate.getYear() << "/" << secondDate.getMonth() << "/" << secondDate.getDay() << endl;

		for (int i = 0; i < hallCount; i++)
		{
			boughtTicketsReportFile << "Hall No: " << (i + 1) << ": " << endl;
			int eventCounter = 0;
			for (int j = 0; j < eventCount; j++)
			{
				if (events[j].getHall() == halls[i] && ((events[j].getDate() > firstDate
					&& events[j].getDate() < secondDate) || events[j].getDate() == firstDate || events[j].getDate() == secondDate))
				{
					eventCounter++;
					boughtTicketsReportFile << eventCounter << ". " << events[j].getName() << "|" << events[j].getDate() <<
						"|Count of bought tickets: " << events[j].getBoughtSeatCount() << endl;
				}
			}
			boughtTicketsReportFile << "---------------------------------------------------------" << endl;
		}

		boughtTicketsReportFile.close();
	}
	else
	{
		Hall hall = halls[toInt(hallStr) - 1];

		char fileName[100] = "report-boughttickets-hall-";
		strcat_s(fileName, hallStr);
		strcat_s(fileName, "-");
		strcat_s(fileName, convertFromDateToString(firstDate));
		strcat_s(fileName, "-");
		strcat_s(fileName, convertFromDateToString(secondDate));
		strcat_s(fileName, ".txt");

		boughtTicketsReportFile.open(fileName);
		if (!boughtTicketsReportFile.is_open()) throw "A file with such name can't be opened!";

		boughtTicketsReportFile << "*Report for bought tickets*" << endl;
		boughtTicketsReportFile << firstDate.getYear() << "/" << firstDate.getMonth() << "/" << firstDate.getDay() << "-"
								<< secondDate.getYear() << "/" << secondDate.getMonth() << "/" << secondDate.getDay() << endl;
		boughtTicketsReportFile << "Hall No: " << hallStr << ": " << endl;
		int eventCounter = 0;

		for (int i = 0; i < eventCount; i++)
		{
			if (events[i].getHall() == hall && ((events[i].getDate() > firstDate
				&& events[i].getDate() < secondDate) || events[i].getDate() == firstDate || events[i].getDate() == secondDate))
			{
				eventCounter++;
				boughtTicketsReportFile << eventCounter << ". " << events[i].getName() << "|" << events[i].getDate() <<
					"|Count of bought tickets: " << events[i].getBoughtSeatCount() << endl;
			}
		}

		boughtTicketsReportFile.close();
	}
}

//Bonus functions
void printMostWatchedEventsReport()
{
	cout << endl << "---------Report for most watched events-----------------" << endl;

	//Create buffer array to store the events
	Event* sortedEvents = new (nothrow) Event[eventCount];
	if (!sortedEvents) throw "Memory problem!";

	for (int i = 0; i < eventCount; i++)
	{
		sortedEvents[i] = events[i];
	}

	bool isEventsSorted = false;

	//Sort the events by count of bought tickets
	while (!isEventsSorted)
	{
		isEventsSorted = true;

		for (int i = 0; i < eventCount; i++)
		{
			if (i != eventCount - 1 && sortedEvents[i].getBoughtSeatCount() < sortedEvents[i + 1].getBoughtSeatCount())
			{
				Event prevBufferEvent = Event(sortedEvents[i].getDate(), sortedEvents[i].getName(), sortedEvents[i].getHall());
				sortedEvents[i] = sortedEvents[i + 1];
				sortedEvents[i + 1] = prevBufferEvent;
				isEventsSorted = false;
			}
		}
	}
	
	//Creating the file
	ofstream mostWatchedEventsReportFile("report-mostWatchedEvents.txt");
	if (!mostWatchedEventsReportFile.is_open()) throw "A file with such name can't be opened!";

	int counter = (eventCount < 3) ? eventCount : 3;

	//Writing to the file
	mostWatchedEventsReportFile << "*Report for most watched events*" << endl;

	for (int i = 0; i < counter; i++)
	{
		mostWatchedEventsReportFile << (i + 1) << ". " << sortedEvents[i].getName() << "|" << sortedEvents[i].getDate()
								   << "| " << "Count of bought tickets: " << sortedEvents[i].getBoughtSeatCount() << " of "
								   << events[i].getHall().getRowCount() * events[i].getHall().getSeatCountInRow() << endl;
	}

	delete[] sortedEvents;
	mostWatchedEventsReportFile.close();
}

void printEventsWithUnder10PercentReport()
{
	cout << endl << "---------Report for events with under 10% attendance-----------------" << endl;

	Date firstDate;
	Date secondDate;

	//Two inputs
	cout << "Enter the first date: ";
	cin >> firstDate;

	cout << "Enter the second date: ";
	do
	{
		cin >> secondDate;
	} while (firstDate > secondDate);

	cin.ignore();

	ofstream eventsWithUnder10PercentReportFile("report-eventsWithUnder10PercentAttendance.txt");
	if (!eventsWithUnder10PercentReportFile.is_open()) throw "A file with such name can't be opened!";

	//Writing to the file
	eventsWithUnder10PercentReportFile << "*Report for events with under 10% attendance*" << endl;
	eventsWithUnder10PercentReportFile << firstDate.getYear() << "/" << firstDate.getMonth() << "/" << firstDate.getDay() << "-"
		<< secondDate.getYear() << "/" << secondDate.getMonth() << "/" << secondDate.getDay() << endl;

	for (int i = 0; i < eventCount; i++)
	{
		int allSeatCount = events[i].getHall().getRowCount() * events[i].getHall().getSeatCountInRow();

		if (((events[i].getDate() > firstDate&& events[i].getDate() < secondDate) || events[i].getDate() == firstDate
			|| events[i].getDate() == secondDate) && events[i].getBoughtSeatCount() < (0.1 * allSeatCount))
		{
			eventsWithUnder10PercentReportFile << (i + 1) << ". " << events[i].getName() << "|" << events[i].getDate()
				<< "| " << "Count of bought tickets: " << events[i].getBoughtSeatCount() << " of "
				<< allSeatCount << endl;
		}
	}

	eventsWithUnder10PercentReportFile.close();
}

//Dialogue functions
void printCommandList()
{
	cout << "list / clear / stop / add new event / reserve ticket / cancel reservation / buy ticket" << endl;
	cout << "print free seats report / print reservation report / print bought tickets report" << endl;
	cout << "print most watched report / print under 10 % report" << endl;
}

void executeCommand(char command[])
{
	if (!strcmp(command, "list"))
		printCommandList();
	else if (!strcmp(command, "clear"))
		system("cls");
	else if (!strcmp(command, "stop"))
		return;
	else if (!strcmp(command, "add new event"))
		addNewEvent();
	else if (!strcmp(command, "reserve ticket"))
		reserveTicket();
	else if (!strcmp(command, "cancel reservation"))
		cancelReservation();
	else if (!strcmp(command, "buy ticket"))
		buyTicket();
	else if (!strcmp(command, "print free seats report"))
		printFreeSeatsReport();
	else if (!strcmp(command, "print reservation report"))
		printReservationReport();
	else if (!strcmp(command, "print bought tickets report"))
		printBoughtTicketsReport();
	else if (!strcmp(command, "print most watched report"))
		printMostWatchedEventsReport();
	else if (!strcmp(command, "print under 10 % report"))
		printEventsWithUnder10PercentReport();
	else
		cout << "Invalid command!" << endl;
}

int main()
{
	saveAndLoadHallsAndEventsFromFiles();

	char command[100];
	do
	{
		cout << endl << "Type a command (use 'list' for help)" << endl;
		cout << ">";
		cin.getline(command, 100);
		executeCommand(command);
	} while (strcmp(command, "stop"));

	saveEventsToFile();
	saveHallsToFile();
	freeHeapMemory();
	return 0;
}