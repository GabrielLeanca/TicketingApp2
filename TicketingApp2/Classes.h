#pragma once

#include <iostream>
#include <string>
#include <random>
#include <ctime>
using namespace std;

enum ticketType {
	VIP, CATEGORY1, CATEGORY2, CATEGORY3, OTHER
};

ticketType operator++(ticketType& type){
	switch (type)
	{
	case VIP:
		type = CATEGORY1;
		break;
	case CATEGORY1:
		type = CATEGORY2;
		break;
	case CATEGORY2:
		type = CATEGORY3;
		break;
	default:
		type = OTHER;
	}
	return type;
}

ostream& operator<<(ostream& console, ticketType type) {
	switch (type)
	{
	case VIP:
		console << "VIP";
		break;
	case CATEGORY1:
		console << "CATEGORY1";
		break;
	case CATEGORY2:
		console << "CATEGORY2";
		break;
	case CATEGORY3:
		console << "CATEGORY3";
		break;
	default:
		console << "OTHER";
	}
	return console;
}

class Event;
class Ticket;
class Location;
class LocSeats;

class Location {
	

	
protected:
	bool isLocSeats = 0;
	static Location** vectLoc;
	static int noLoc;

	

	const string address = "";
	char* name = nullptr;
	int capacity = 0;
	//int rows = 0;
	int* ticketsSoldPreviously = nullptr;
	int noPreviousEvents = 0;

	float rating = 2.5; //can have 0 to 5 stars
	int ratingWeight = 0;

	void init() {
		name = nullptr;
		capacity = 0;
		ticketsSoldPreviously = nullptr;
		noPreviousEvents = 0;
		rating = 2.5;
		ratingWeight = 0;
		isLocSeats = 0;
	}

	void init(string name, int capacity) {
		if (capacity < 0)
			throw exception("negative values not allowed");
		this->name = new char[strlen(name.c_str()) + 1];
		strcpy_s(this->name, strlen(name.c_str()) + 1, name.c_str());
		this->capacity = capacity;
		ticketsSoldPreviously = nullptr;
		noPreviousEvents = 0;
		rating = 2.5;
		ratingWeight = 0;
		isLocSeats = 0;
	}

	void init(Location& location) {
		delete[] this->name;
		if (location.name == nullptr) {
			this->name = nullptr;
		}
		else {
			this->name = new char[strlen(location.name) + 1];
			strcpy_s(this->name, strlen(location.name) + 1, location.name);
		}
		this->capacity = location.capacity;
		delete[] this->ticketsSoldPreviously;
		if (location.ticketsSoldPreviously != nullptr) {
			this->ticketsSoldPreviously = new int[location.noPreviousEvents];
			for (int i = 0; i < location.noPreviousEvents; i++) {
				this->ticketsSoldPreviously[i] = location.ticketsSoldPreviously[i];
			}
		}
		else {
			this->ticketsSoldPreviously = nullptr;
		}
		this->noPreviousEvents = location.noPreviousEvents;
		this->rating = location.rating;
		this->ratingWeight = location.ratingWeight;
		this->isLocSeats = 0;
	}
	void deconstruct() {
		delete[] this->name;
		delete[] this->ticketsSoldPreviously;
	}
public:
	void addElementToArray() {
		if (vectLoc != nullptr)
		{
			Location** aux = new Location * [noLoc];
			for (int i = 0; i < noLoc; i++) {
				aux[i] = vectLoc[i];
			}
			delete[] vectLoc;
			vectLoc = new Location * [noLoc + 1];
			for (int i = 0; i < noLoc; i++) {
				vectLoc[i] = aux[i];
			}
			delete[] aux;
			vectLoc[noLoc] = this;
		}
		else {
			vectLoc = new Location * [1];
			vectLoc[0] = this;
		}
		noLoc++;
	}

	void removeElementFromArray() {
		if (vectLoc == nullptr)
			throw exception("empty array");
		Location** aux = new Location * [noLoc - 1];
		int i;
		for (i = 0; i < noLoc - 1; i++) {
			if (vectLoc[i] == this)
				break;
			aux[i] = vectLoc[i];
		}
		for (i; i < noLoc - 1; i++) {
			aux[i] = vectLoc[i + 1];
		}
		delete[] vectLoc;
		vectLoc = new Location * [noLoc - 1];
		for (i = 0; i < noLoc - 1; i++) {
			vectLoc[i] = aux[i];
		}
		delete[] aux;
		noLoc--;
	}

	Location(string address) :address("") {
	}

	Location() :address("") {
		init();
	}

	Location(string address, string name, int capacity) :address(address) {
		init(name, capacity);
	}

	Location(Location& location) :address(location.address) {
		init(location);
	}

	void operator=(Location& location) {
		delete[] this->name;
		if (location.name == nullptr) {
			this->name = nullptr;
		}
		else {
			this->name = new char[strlen(location.name) + 1];
			strcpy_s(this->name, strlen(location.name) + 1, location.name);
		}
		this->capacity = location.capacity;
		delete[] this->ticketsSoldPreviously;
		if (location.ticketsSoldPreviously != nullptr) {
			this->ticketsSoldPreviously = new int[location.noPreviousEvents];
			for (int i = 0; i < location.noPreviousEvents; i++) {
				this->ticketsSoldPreviously[i] = location.ticketsSoldPreviously[i];
			}
		}
		else {
			this->ticketsSoldPreviously = nullptr;
		}
		this->noPreviousEvents = location.noPreviousEvents;
		this->rating = location.rating;
		this->ratingWeight = location.ratingWeight;
	}

	~Location() {
		deconstruct();
	}

	string getAddress() {
		return address;
	}

	char* getName() {
		if (this->name == nullptr) {
			return nullptr;
		}
		char* copy = new char[strlen(this->name) + 1];
		strcpy_s(copy, strlen(this->name) + 1, this->name);
		return copy;
	}

	void setName(string name) {
		this->name = new char[strlen(name.c_str()) + 1];
		strcpy_s(this->name, strlen(name.c_str()) + 1, name.c_str());
	}

	int getCapacity() {
		return this->capacity;
	}

	void setCapacity(int capacity) {
		if (capacity < 0)
			throw exception("negative values not allowed");
		this->capacity = capacity;
	}

	int* getTicketsSoldPreviously() {
		int* copy = new int[noPreviousEvents];
		for (int i = 0; i < noPreviousEvents; i++)
			copy[i] = ticketsSoldPreviously[i];
		return copy;
	}

	void setTicketsSoldPreviously(int* array, int noElem) {
		if (noElem < 0)
			throw exception("negative values not allowed");
		delete[] ticketsSoldPreviously;
		if (noElem == 0) {
			ticketsSoldPreviously = nullptr;
		}
		if (noElem > 0) {
			ticketsSoldPreviously = new int[noElem];
			for (int i = 0; i < noElem; i++) {
				ticketsSoldPreviously[i] = array[i];
			}
		}
		this->noPreviousEvents = noElem;
	}

	int getNoPreviousEvents() {
		return this->noPreviousEvents;
	}

	float getRating() {
		return this->rating;
	}

	void setRating(float rating, int noReviews) {
		if (rating < 0 || rating>5 || noReviews < 0)
			throw exception("outside range");
		this->rating = rating;
		this->ratingWeight = noReviews;
	}

	int getRatingWeight() {
		return this->ratingWeight;
	}

	static Location** getVectLoc() {
		Location** copy = new Location * [noLoc];
		for (int i = 0; i < noLoc; i++) {
			copy[i] = vectLoc[i];
		}
		return copy;
	}

	int& operator[](int index) {
		if (index < 0 || index >= noPreviousEvents)
			throw exception("outside range");
		return this->ticketsSoldPreviously[index];
	}

	void finishCurrentEvent(Event& event);


	void operator=(float review) {
		if (review < 0 || review>5)
			throw exception("review out of range");
		this->rating = (this->rating * this->ratingWeight + review) / (this->ratingWeight + 1);
		this->ratingWeight++;
	}

	bool operator!() {
		if (this->name == nullptr)
			return 1;
		return 0;
	}

	void setMinimumPriceForLocation(float price);

	void addElementToTicketArray(int newElem) {
		int* aux = new int[noPreviousEvents];
		for (int i = 0; i < noPreviousEvents; i++) {
			aux[i] = ticketsSoldPreviously[i];
		}
		delete[] ticketsSoldPreviously;
		noPreviousEvents++;
		ticketsSoldPreviously = new int[noPreviousEvents];
		for (int i = 0; i < noPreviousEvents - 1; i++) {
			ticketsSoldPreviously[i] = aux[i];
		}
		delete[] aux;
		ticketsSoldPreviously[noPreviousEvents - 1] = newElem;
	}

	static int getNoLoc() {
		return noLoc;
	}

	static Location& getLocation(int index) {
		if (index < 0 || index >= noLoc)
			throw exception("outside range");
		return *vectLoc[index];
	}

	friend ostream& operator<<(ostream& console, Location& location);
	friend istream& operator>>(istream& console, Location& location);
};

ostream& operator<<(ostream& console, Location& location) {
	console << endl << "Name: " << location.name;
	console << endl << "Address: " << location.address;
	console << endl << "Max Seats: " << location.capacity;
	for (int i = 0; i < location.noPreviousEvents; i++)
		console << endl << "event " << i << ": " << location.ticketsSoldPreviously[i];
	console << endl << "Number of previous events: " << location.noPreviousEvents;
	console << endl << "Rating: " << location.rating << "/5 stars";
	console << endl << "Reviews: " << location.ratingWeight;
	return console;
}

istream& operator>>(istream& console, Location& location) {
	string newName;
	cout << endl << "Name: ";
	console >> newName;
	delete[] location.name;
	location.name = new char[strlen(newName.c_str()) + 1];
	strcpy_s(location.name, strlen(newName.c_str()) + 1, newName.c_str());
	cout << endl << "Capacity: ";
	console >> location.capacity;
	if (location.capacity < 0)
		throw exception("negative values not allowed");
	cout << endl << "Number of previous events: ";
	console >> location.noPreviousEvents;
	if (location.noPreviousEvents < 0)
		throw exception("negative values not allowed");
	delete[] location.ticketsSoldPreviously;
	location.ticketsSoldPreviously = new int[location.noPreviousEvents];
	for (int i = 0; i < location.noPreviousEvents; i++) {
		cout << endl << "Tickets sold for event " << i << ": ";
		console >> location.ticketsSoldPreviously[i];
		if (location.ticketsSoldPreviously[i] < 0)
			throw exception("review out of range");
	}
	if (location.noPreviousEvents == 0)
		location.ticketsSoldPreviously = nullptr;
	cout << endl << "Rating: ";
	console >> location.rating;
	cout << endl << "No reviews: ";
	console >> location.ratingWeight;
	if (location.rating < 0 || location.rating > 5 || location.ratingWeight < 0)
		throw exception("negative values not allowed");
	return console;
}

Location** Location::vectLoc = nullptr;
int Location::noLoc = 0;


class Seat {
	bool occupied = 0;
	ticketType type = OTHER;

public:
	Seat(ticketType type) {
		this->type = type;
		occupied = 0;
	}

	ticketType getType() {
		return type;
	}

	void setType(ticketType zone) {
		if (zone != 0 && zone != 1 && zone != 2 && zone != 3)
			this->type = OTHER;
		else
			this->type = zone;
	}
};

class LocSeats :public Location {
protected:
	Seat*** arrSeats = nullptr;
	int noRows = 0;
	int seatsPerRow = 0;
	
public:
	
	LocSeats() :Location() {
		isLocSeats = 1;
	}

	~LocSeats(){
		if (arrSeats != nullptr) {
			for (int i = 0; i < noRows; i++) {
				for (int j = 0; j < seatsPerRow; j++) {
					delete arrSeats[i][j];
				}
				delete[] arrSeats[i];
			}
			delete[] arrSeats;
		}
	}
	
	LocSeats(string address, string name, int capacity) : Location(address, name, capacity) {
		isLocSeats = 1;
	}

	LocSeats(string address, string name, int capacity, int noRows, int noSeatsPerRow) : Location(address, name, capacity) {
		if (noRows < 0 || noSeatsPerRow < 0) {
			throw exception("no negative values allowed");
		}
		this->noRows = noRows;
		this->seatsPerRow = noSeatsPerRow;
		arrSeats = new Seat * *[noRows];
		for (int i = 0; i < noRows; i++) {
			arrSeats[i] = new Seat * [noSeatsPerRow];
			for (int j = 0; j < noSeatsPerRow; j++) {
				arrSeats[i][j]  = new Seat(OTHER);
			}
		}
		isLocSeats = 1;
	}
	
	LocSeats(Location& location) : Location(location) {
		arrSeats = nullptr;
		seatsPerRow = 0;
		noRows = 0;
		isLocSeats = 1;
	}

	LocSeats(LocSeats& location) : Location(location) {
		this->noRows = location.noRows;
		this->seatsPerRow = location.seatsPerRow;
		if (this->noRows > 0 && this->seatsPerRow > 0) {
			this->arrSeats = new Seat * *[this->noRows];
			for (int i = 0; i < this->noRows; i++) {
				this->arrSeats[i] = new Seat * [this->seatsPerRow];
				for (int j = 0; j < this->seatsPerRow; j++) {
					this->arrSeats[i][j] = new Seat(OTHER);
				}
			}
		}
		else {
			arrSeats = nullptr;
		}
		isLocSeats = 1;
	}

	int getNoRows() {
		return noRows;
	}

	int getSeatsPerRow() {
		return seatsPerRow;
	}
	
	Seat*** getArrSeats() {
		if (arrSeats == nullptr)
			return nullptr;
		Seat*** copy = new Seat * *[noRows];
		for (int i = 0; i < this->noRows; i++) {
			copy[i] = new Seat * [this->seatsPerRow];
			for (int j = 0; j < this->seatsPerRow; j++) {
				copy[i][j] = arrSeats[i][j];
			}
		}
		return copy;
	}
	
	friend ostream& operator<<(ostream& console, LocSeats& location);
	friend istream& operator>>(istream& console, LocSeats& location);
};

ostream& operator<<(ostream& console, LocSeats& location) {
	console << endl << "Name: " << location.name;
	console << endl << "Address: " << location.address;
	console << endl << "Max Seats: " << location.capacity;
	for (int i = 0; i < location.noPreviousEvents; i++)
		console << endl << "event " << i << ": " << location.ticketsSoldPreviously[i];
	console << endl << "Number of previous events: " << location.noPreviousEvents;
	console << endl << "Rating: " << location.rating << "/5 stars";
	console << endl << "Reviews: " << location.ratingWeight;
	console << endl << "No Rows: " << location.noRows;
	console << endl << "Seats per Row: " << location.seatsPerRow;
	return console;
}

istream& operator>>(istream& console, LocSeats& location) {
	string newName;
	cout << endl << "Name: ";
	console >> newName;
	delete[] location.name;
	location.name = new char[strlen(newName.c_str()) + 1];
	strcpy_s(location.name, strlen(newName.c_str()) + 1, newName.c_str());
	cout << endl << "Capacity: ";
	console >> location.capacity;
	if (location.capacity < 0)
		throw exception("negative values not allowed");
	cout << endl << "Number of previous events: ";
	console >> location.noPreviousEvents;
	if (location.noPreviousEvents < 0)
		throw exception("negative values not allowed");
	delete[] location.ticketsSoldPreviously;
	location.ticketsSoldPreviously = new int[location.noPreviousEvents];
	for (int i = 0; i < location.noPreviousEvents; i++) {
		cout << endl << "Tickets sold for event " << i << ": ";
		console >> location.ticketsSoldPreviously[i];
		if (location.ticketsSoldPreviously[i] < 0)
			throw exception("review out of range");
	}
	if (location.noPreviousEvents == 0)
		location.ticketsSoldPreviously = nullptr;
	cout << endl << "Rating: ";
	console >> location.rating;
	cout << endl << "No reviews: ";
	console >> location.ratingWeight;
	if (location.rating < 0 || location.rating > 5 || location.ratingWeight < 0)
		throw exception("negative values not allowed");
	cout << endl << "No rows: ";
	console >> location.noRows;
	cout << endl << "No seats per row: ";
	console >> location.seatsPerRow;
	return console;
}

class Event {
protected:
	char* name = nullptr;
	char date[11] = { 0 };
	char time[6] = { 0 };
	int ticketsSold = 0;
	float ticketPrice[5] = { -1 };
	Location* location = nullptr;

	static Event** vectEv;
	static int noEv;

	
public:

	void addElementToArray() {
		if (vectEv != nullptr)
		{
			Event** aux = new Event * [noEv];
			for (int i = 0; i < noEv; i++) {
				aux[i] = vectEv[i];
			}
			delete[] vectEv;
			vectEv = new Event * [noEv + 1];
			for (int i = 0; i < noEv; i++) {
				vectEv[i] = aux[i];
			}
			delete[] aux;
			vectEv[noEv] = this;
		}
		else {
			vectEv = new Event * [1];
			vectEv[0] = this;
		}
		noEv++;
	}

	void removeElementFromArray() {
		if (vectEv == nullptr)
			throw exception("empty array");
		Event** aux = new Event * [noEv - 1];
		int i;
		for (i = 0; i < noEv - 1; i++) {
			if (vectEv[i] == this)
				break;
			aux[i] = vectEv[i];
		}
		for (i; i < noEv - 1; i++) {
			aux[i] = vectEv[i + 1];
		}
		delete[] vectEv;
		vectEv = new Event * [noEv - 1];
		for (i = 0; i < noEv - 1; i++) {
			vectEv[i] = aux[i];
		}
		delete[] aux;
		noEv--;
	}

	Event() {
		name = nullptr;
		strcpy_s(date, 11, "00/00/0000"); // dd/mm/yyyy
		strcpy_s(time, 6, "00:00"); // hh:mm
		ticketsSold = 0;
		location = nullptr;
		for (int i = 0; i < 5; i++) {
			ticketPrice[i] = -1;
		}
	}

	Event(string name, string date, string time, Location& location) {
		this->name = new char[strlen(name.c_str()) + 1];
		strcpy_s(this->name, strlen(name.c_str()) + 1, name.c_str());
		if (strlen(date.c_str()) != 10) {
			throw exception("Invalid date");
		}
		if (date[2] != '/' || date[5] != '/') {
			throw exception("Invalid date");
		}
		strcpy_s(this->date, 11, date.c_str());
		if (strlen(time.c_str()) != 5) {
			throw exception("Invalid time");
		}
		if (time[2] != ':') {
			throw exception("Invalid time");
		}
		strcpy_s(this->time, 6, time.c_str());
		this->ticketsSold = 0;
		this->location = &location;
		for (int i = 0; i < 5; i++) {
			ticketPrice[i] = -1;
		}
	}

	Event(Event& event) {
		this->name = new char[strlen(event.name) + 1];
		strcpy_s(this->name, strlen(event.name) + 1, event.name);
		if (strlen(event.date) != 10) {
			throw exception("Invalid date");
		}
		if (event.date[2] != '/' || event.date[5] != '/') {
			throw exception("Invalid date");
		}
		strcpy_s(this->date, 11, event.date);
		if (strlen(event.time) != 5) {
			throw exception("Invalid time");
		}
		if (event.time[2] != ':') {
			throw exception("Invalid time");
		}
		strcpy_s(this->time, 6, event.time);
		this->ticketsSold = 0;
		this->location = event.location;
		for (int i = 0; i < 5; i++) {
			this->ticketPrice[i] = event.ticketPrice[i];
		}
	}

	void operator=(Event& event) {
		this->name = new char[strlen(event.name) + 1];
		strcpy_s(this->name, strlen(event.name) + 1, event.name);
		if (strlen(event.date) != 10) {
			throw exception("Invalid date");
		}
		if (event.date[2] != '/' || event.date[5] != '/') {
			throw exception("Invalid date");
		}
		strcpy_s(this->date, 11, event.date);
		if (strlen(event.time) != 5) {
			throw exception("Invalid time");
		}
		if (event.time[2] != ':') {
			throw exception("Invalid time");
		}
		strcpy_s(this->time, 6, event.time);
		this->ticketsSold = event.ticketsSold;
		this->location = event.location;
		for (int i = 0; i < 5; i++) {
			this->ticketPrice[i] = event.ticketPrice[i];
		}
	}

	~Event() {
		delete[] name;
	}

	friend ostream& operator<<(ostream& console, Event& event);
	friend istream& operator>>(istream& console, Event& event);

	float getTicketPrice(int type) {
		return ticketPrice[type];
	}

	void setTicketPrice() {
		for (int i = 0; i < 5; i++)
			cin >> ticketPrice[i];
	}

	char* getName() {
		if (this->name == nullptr) {
			return nullptr;
		}
		char* copy = new char[strlen(this->name) + 1];
		strcpy_s(copy, strlen(this->name) + 1, this->name);
		return copy;
	}

	void setName(string name) {
		this->name = new char[strlen(name.c_str()) + 1];
		strcpy_s(this->name, strlen(name.c_str()) + 1, name.c_str());
	}

	char* getDate() {
		char* copy = new char[11];
		strcpy_s(copy, 11, this->date);
		return copy;
	}

	void setDate(string date) {
		if (strlen(date.c_str()) != 10) {
			throw exception("Invalid date");
		}
		if (date[2] != '/' || date[5] != '/') {
			throw exception("Invalid date");
		}
		strcpy_s(this->date, 11, date.c_str());
	}

	char* getTime() {
		char* copy = new char[6];
		strcpy_s(copy, 6, this->time);
		return copy;
	}

	void setTime(string time) {
		if (strlen(time.c_str()) != 5) {
			throw exception("Invalid time");
		}
		if (time[2] != ':') {
			throw exception("Invalid time");
		}
		strcpy_s(this->time, 6, time.c_str());
	}

	int getTicketsSold() {
		return ticketsSold;
	}

	void setTicketsSold(int sold) { //avoid using this. this variable tracks number of Ticket objects related to this Event
		if (sold < 0)
			throw exception("negative value not allowed for tickets currently sold");
		this->ticketsSold = sold;
	}

	Location* getLocation() {
		return this->location;
	}

	void setLocation(Location& location) {
		this->location = &location;
	}

	Event operator++(int) {
		Event copy = *this;
		this->ticketsSold++;
		return copy;
	}

	Event& operator++() {
		this->ticketsSold++;
		return *this;
	}

	Event operator--(int) {
		if (this->ticketsSold == 0)
			throw exception("negative value not allowed for tickets currently sold");
		Event copy = *this;
		this->ticketsSold--;
		return copy;
	}

	Event& operator--() {
		if (this->ticketsSold == 0)
			throw exception("negative value not allowed for tickets currently sold");
		this->ticketsSold--;
		return *this;
	}

	bool operator>(Event event) {
		if (this->ticketsSold > event.ticketsSold)
			return 1;
		return 0;
	}

	bool operator>=(Event event) {
		if (this->ticketsSold >= event.ticketsSold)
			return 1;
		return 0;
	}

	bool operator==(Event event) {
		if (this->ticketsSold == event.ticketsSold)
			return 1;
		return 0;
	}

	bool operator<=(Event event) {
		if (this->ticketsSold <= event.ticketsSold)
			return 1;
		return 0;
	}

	bool operator<(Event event) {
		if (this->ticketsSold < event.ticketsSold)
			return 1;
		return 0;
	}
	
	
	static int getNoEv() {
		return noEv;
	}
	
	static Event& getEvent(int index) {
		if (index < 0 || index >= noEv)
			throw exception("outside range");
		return *vectEv[index];
	}

	//float calculateFutureRevenue();
	void setTicketPriceForEvent(float price);
};

ostream& operator<<(ostream& console, Event& event) {

	if (event.name != nullptr)
		console << endl << "Name: " << event.name;
	console << endl << "Date: ";
	for (int i = 0; i < 10; i++) {
		console << event.date[i];
	}
	cout << endl << "Time: ";
	for (int i = 0; i < 5; i++) {
		console << event.time[i];
	}
	console << endl << "Tickets sold: " << event.ticketsSold;
	if (event.location != nullptr)
		console << endl << "Location: " << event.location->getName();
	return console;
}

istream& operator>>(istream& console, Event& event) {
	string newParameter;
	cout << endl << "Name: ";
	console >> newParameter;
	delete[] event.name;
	event.name = new char[strlen(newParameter.c_str()) + 1];
	strcpy_s(event.name, strlen(newParameter.c_str()) + 1, newParameter.c_str());
	cout << endl << "Date (use the format dd/mm/yyyy): ";
	console >> newParameter;
	if (strlen(newParameter.c_str()) != 10) {
		throw exception("Invalid date");
	}
	if (newParameter[2] != '/' || newParameter[5] != '/') {
		throw exception("Invalid date");
	}
	strcpy_s(event.date, 11, newParameter.c_str());
	cout << endl << "Time (use the format hh:mm): ";
	console >> newParameter;
	if (strlen(newParameter.c_str()) != 5) {
		throw exception("Invalid time");
	}
	if (newParameter[2] != ':') {
		throw exception("Invalid time");
	}
	strcpy_s(event.time, 6, newParameter.c_str());
	//cout << endl << "No tickets sold: ";	//tickets sold tracks ammout of instances of Ticket objects. avoid changing it
	//console >> event.ticketsSold;
	//if (event.ticketsSold < 0)
	//	throw exception("negative value not allowed for tickets currently sold");
	return console;
}

Event** Event::vectEv = nullptr;
int Event::noEv = 0;

class Ticket {
protected:
	int id = -1;
	Event* event = nullptr;
	ticketType zone = OTHER;
	float price = 0;

	//static int ticketsSold;
	static Ticket** vectTk;
	static int noTk;


	static int generateTicketId() {
		int randomID;
		bool ok = 0;
		if (noTk == RAND_MAX) { //ticketsSold cant hold higher values
			throw exception("Maximum number of tickets reached");
		}
		while (ok == 0) {
			randomID = rand();
			ok = 1;
			for (int i = 0; i < noTk; i++) {
				if (randomID == vectTk[i]->id) {
					ok = 0;
				}
			}
		}
		return randomID;
	}

	

public:

	void addElementToArray() {
		if (vectTk != nullptr)
		{
			Ticket** aux = new Ticket * [noTk];
			for (int i = 0; i < noTk; i++) {
				aux[i] = vectTk[i];
			}
			delete[] vectTk;
			vectTk = new Ticket * [noTk + 1];
			for (int i = 0; i < noTk; i++) {
				vectTk[i] = aux[i];
			}
			delete[] aux;
			vectTk[noTk] = this;
		}
		else {
			vectTk = new Ticket * [1];
			vectTk[0] = this;
		}
		noTk++;
	}

	void removeElementFromArray() {
		if (vectTk == nullptr)
			throw exception("empty array");
		Ticket** aux = new Ticket * [noTk - 1];
		int i;
		for (i = 0; i < noTk - 1; i++) {
			if (vectTk[i] == this)
				break;
			aux[i] = vectTk[i];
		}
		for (i; i < noTk - 1; i++) {
			aux[i] = vectTk[i + 1];
		}
		delete[] vectTk;
		vectTk = new Ticket * [noTk - 1];
		for (i = 0; i < noTk - 1; i++) {
			vectTk[i] = aux[i];
		}
		delete[] aux;
		noTk--;
	}

	Ticket() {
		id = generateTicketId();
		event = nullptr;
		zone = OTHER;
		price = 0;
	}

	Ticket(Event& event, ticketType zone, float price) {
		this->id = generateTicketId();
		this->event = &event;
		this->zone = zone;
		if (price < 0)
			throw exception("negative value not allowed for price");
		this->price = price;
		if (this->event != nullptr)
			(*this->event)++;
	}

	Ticket(Ticket& ticket) {
		this->id = generateTicketId();
		this->event = ticket.event;
		this->zone = ticket.zone;
		if (this->event != nullptr)
			(*this->event)++;
		this->price = ticket.price;
	}

	void operator=(Ticket& ticket) {
		if (this->event != nullptr)
			(*this->event)--;
		this->event = ticket.event;
		this->zone = ticket.zone;
		if (this->event != nullptr)
			(*this->event)++;
		this->price = ticket.price;
	}

	~Ticket() {
		//if (this->event != nullptr)
		//	(*this->event)--;
	}

	float operator+(float nr) {
		return this->price + nr;
	}

	float operator-(float nr) {
		return this->price - nr;
	}

	float operator*(float nr) {
		return this->price * nr;
	}

	float operator/(float nr) {
		return this->price / nr;
	}

	static void removeDefaultTickets() {
		for (int i = 0; i < noTk; i++) {
			if (vectTk[i]->id == -1)
				vectTk[i]->removeElementFromArray();
		}
	}

	float getPrice() {
		return this->price;
	}

	void setPrice(float price) {
		if (price < 0) {
			throw exception("negative value not allowed for price");
		}
		this->price = price;
	}

	int getId() {
		return this->id;
	}

	Event* getEvent() {
		return this->event;
	}

	void setEvent(Event* event) {
		(*this->event)--;
		this->event = event;
		(*this->event)++;
	}

	ticketType getZone() {
		return this->zone;
	}

	void setZone(ticketType zone) {
		if (zone != 0 && zone != 1 && zone != 2 && zone != 3)
			this->zone = OTHER;
		else
			this->zone = zone;
	}

	static int getNoTk() {
		return noTk;
	}

	static Ticket** getVectTk() {
		Ticket** copy = new Ticket * [noTk];
		for (int i = 0; i < noTk; i++) {
			copy[i] = vectTk[i];
		}
		return copy;
	}

	//TicketList is a list of all existing tickets. creating/deleting a ticket will always update the list

	static Ticket& getTicket(int index) {
		if (index < 0 || index >= noTk)
			throw exception("outside range");
		return *vectTk[index];
	}

	friend ostream& operator<<(ostream& console, Ticket& ticket);
	friend istream& operator>>(istream& console, Ticket& ticket);




};


ostream& operator<<(ostream& console, Ticket& ticket) {
	console << endl << "Id: " << ticket.id;
	if (ticket.event != nullptr) {
		console << endl << "Event: " << ticket.event->getName();
	}
	switch (ticket.zone) //VIP, CATEGORY1, CATEGORY2, CATEGORY3, OTHER
	{
	case 0:
		console << endl << "Ticket type: VIP";
		break;
	case 1:
		console << endl << "Ticket type: CATEGORY1";
		break;
	case 2:
		console << endl << "Ticket type: CATEGORY2";
		break;
	case 3:
		console << endl << "Ticket type: CATEGORY3";
		break;
	default:
		console << endl << "Ticket type: OTHER";
	}
	console << endl << "Price: " << ticket.price;
	return console;
}

istream& operator>>(istream& console, Ticket& ticket) {
	string newParameter;
	cout << endl << "Ticket zone/type (choose between VIP, CATEGORY1, CATEGORY2, CATEGORY3, OTHER): ";
	console >> newParameter;
	if (newParameter != "VIP" && newParameter != "CATEGORY1" && newParameter != "CATEGORY2" && newParameter != "CATEGORY3")
		ticket.zone = OTHER;
	if (newParameter == "VIP")
		ticket.zone = VIP;
	if (newParameter == "CATEGORY1")
		ticket.zone = CATEGORY1;
	if (newParameter == "CATEGORY2")
		ticket.zone = CATEGORY2;
	if (newParameter == "CATEGORY3")
		ticket.zone = CATEGORY3;
	cout << endl << "Price: ";
	console >> ticket.price;
	if (ticket.price < 0)
		throw exception("negative value not allowed for price");
	return console;
}

class STicket : public Ticket {
protected:
	int row = 0;
	int seatOnRow = 0;

public:
	int getRow() {
		return row;
	}

	int getSeatOnRow() {
		return seatOnRow;
	}

	STicket(Event& event, ticketType zone, float price, int row, int seat) : Ticket(event, zone, price) {
		this->row = row;
		this->seatOnRow = seat;
	}
};

Ticket** Ticket::vectTk = nullptr;
int Ticket::noTk = 0;

float operator+(float nr, Ticket ticket) {
	return ticket.getPrice() + nr;
}

float operator-(float nr, Ticket ticket) {
	return nr - ticket.getPrice();
}

float operator*(float nr, Ticket ticket) {
	return ticket.getPrice() * nr;
}

float operator/(float nr, Ticket ticket) {
	return nr / ticket.getPrice();
}


void Location::finishCurrentEvent(Event& event) {
	if (event.getLocation() != this) {
		throw exception("event not taking place at this location");
	}
	this->addElementToTicketArray(event.getTicketsSold());
}


void Location::setMinimumPriceForLocation(float price) {
	for (int i = 0; i < Ticket::getNoTk(); i++) {
		if (Ticket::getTicket(i).getEvent()->getLocation() == this) {
			if (Ticket::getTicket(i).getPrice() < price)
				Ticket::getTicket(i).setPrice(price);
		}
	}
}

/*
float Event::calculateFutureRevenue() {
	float sum = 0;
	for (int i = 0; i < getTicketsSold(); i++) {
		if (Ticket::getTicket(i).getEvent() == this) {
			sum += Ticket::getTicket(i).getPrice();
		}
	}
	return sum;
}*/

void Event::setTicketPriceForEvent(float price) {
	for (int i = 0; i < Ticket::getNoTk(); i++) {
		if (Ticket::getTicket(i).getEvent() == this) {
			Ticket::getTicket(i).setPrice(price);
		}
	}
}

class Menu {
public:
	static void start() {
		cout << endl << "Choose option by typing the digit associted with it and pressing enter (only the first character typed in will be taken into account):";
		cout << endl << "[1] Start as admin" << endl << "[2] Start as customer";
		cout << endl << "[3] Exit" << endl;
		char i;
		i = cin.get();
		if (i == '1') {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			admin();
		}
		if (i == '2') {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			customer();
		}
		if(i!='1' && i!='2' && i!='3'){
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Value not corresponding to an action";
			start();
		}
	}

	static void admin() {
		cout << endl << "[1] Create New Location" << endl << "[2] Inspect/Alter/Remove Location" << endl;
		cout << "[3] Create New Event" << endl << "[4] Inspect/Alter/Remove Event" << endl;
		cout << "[5] Inspect/Alter/Remove Ticket" << endl << "[6] Exit to main menu" << endl;
		char i;
		i = cin.get();
		if (i == '1') {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			createLocation();
		}
	}

	static void createLocation() {
		cout << endl << "[1] Create Location without seats" << endl << "[2] Create Location with seats" << endl;
		cout << "[3] Back to Admin menu" << endl;
		char i;
		i = cin.get();
		if (i == '1') {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Location* location = new Location;
			cin >> *location;
			location->addElementToArray();
			admin();
		}
		if (i == '2') {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			LocSeats* location = new LocSeats;
			cin >> *location;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			location->addElementToArray();
			cout << "[y/n] Customize seat areas?" << endl;
			i = cin.get();
			if (i == 'y') {
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				int vip, cat1, cat2, cat3, other;
				cout << endl << "how many rows are VIP? type an integer: ";
				cin >> vip;
				cout << endl << "how many rows are Category 1? ";
				cin >> cat1;
				cout << endl << "how many rows are Category 2? ";
				cin >> cat2;
				cout << endl << "how many rows are Category 3? ";
				cin >> cat3;
				if (vip + cat1 + cat2 + cat3 > location->getNoRows()) {
					cout << endl << "More seats inserted than present in object. Changes cancelled.";
					cout << endl << "Alter table from Admin menu to add zones";
				}
				else {
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					int index = 0;
					for (index; index < vip; index++) {
						for (int index2 = 0; index2 < location->getSeatsPerRow(); index2++) {
							location->getArrSeats()[index][index2]->setType(VIP);
						}
					}
					for (index; index < cat1; index++) {
						for (int index2 = 0; index2 < location->getSeatsPerRow(); index2++) {
							location->getArrSeats()[index][index2]->setType(CATEGORY1);
						}
					}
					for (index; index < cat2; index++) {
						for (int index2 = 0; index2 < location->getSeatsPerRow(); index2++) {
							location->getArrSeats()[index][index2]->setType(CATEGORY2);
						}
					}
					for (index; index < cat3; index++) {
						for (int index2 = 0; index2 < location->getSeatsPerRow(); index2++) {
							location->getArrSeats()[index][index2]->setType(CATEGORY3);
						}
					}
				}
			}
			admin();
		}
		if (i != '1' && i != '2' && i != '3') {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Value not corresponding to an action";
			admin();
		}
		if (i == '3') {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			admin();
		}
	}

	static void customer() {
		cout << endl << "[1]";
	}
};