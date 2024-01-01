#pragma once

#include <iostream>
#include <string>
#include <random>
using namespace std;

enum ticketType {
	VIP, CATEGORY1, CATEGORY2, CATEGORY3, OTHER
};

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

Location** vectLoc = nullptr;
int noLoc = 0;
Event** vectEv = nullptr;
int noEv = 0;
Ticket** vectTk = nullptr;
int noTk = 0;

class Util {
public:
	static void addElementToArray(Location**& array, int& n, Location& newElem) {
		if (array != nullptr)
		{
			Location** aux = new Location*[n];
			for (int i = 0; i < n; i++) {
				aux[i] = array[i];
			}
			delete[] array;
			array = new Location*[n + 1];
			for (int i = 0; i < n; i++) {
				array[i] = aux[i];
			}
			delete[] aux;
			array[n] = &newElem;
		}
		else {
			array = new Location*[1];
			array[0] = &newElem;
		}
		n++;	
	}

	static void removeElementFromArray(Location**& array, int& n, Location* elem) {
		if (array == nullptr)
			throw exception("empty array");
		Location** aux = new Location*[n-1];
		int i;
		for (i = 0; i < n-1; i++) {
			if (array[i] == elem)
				break;
			aux[i] = array[i];
		}
		for (i; i < n-1; i++) {
			aux[i] = array[i + 1];
		}
		delete[] array;
		array = new Location * [n - 1];
		for (i = 0; i < n - 1; i++) {
			array[i] = aux[i];
		}
		delete[] aux;
		n--;
	}
};

class Location {
protected:
	const string address = "";
	char* name = nullptr;
	int capacity = 0;
	//int rows = 0;
	int* ticketsSoldPreviously = nullptr;
	int noPreviousEvents = 0;

	float rating = 2.5; //can have 0 to 5 stars
	int ratingWeight = 0;
public:
	Location() :address("") {
		name = nullptr;
		capacity = 0;
		//rows = 0;
		ticketsSoldPreviously = nullptr;
		noPreviousEvents = 0;
		rating = 2.5;
		ratingWeight = 0;
		Util::addElementToArray(vectLoc, noLoc, *this);
	}

	Location(string address, string name, int capacity) :address(address) {
		if (capacity < 0)
			throw exception("negative values not allowed");
		this->name = new char[strlen(name.c_str()) + 1];
		strcpy_s(this->name, strlen(name.c_str()) + 1, name.c_str());
		this->capacity = capacity;
		ticketsSoldPreviously = nullptr;
		noPreviousEvents = 0;
		rating = 2.5;
		ratingWeight = 0;
		Util::addElementToArray(vectLoc, noLoc, *this);
	}

	Location(Location& location) :address(location.address) {
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
		Util::addElementToArray(vectLoc, noLoc, *this);
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
		delete[] this->name;
		delete[] this->ticketsSoldPreviously;
		Util::removeElementFromArray(vectLoc, noLoc, this);
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

	int& operator[](int index) {
		if (index < 0 || index >= noPreviousEvents)
			throw exception("outside range");
		return this->ticketsSoldPreviously[index];
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


class Event {
protected:
	char* name = nullptr;
	char date[11] = { 0 };
	char time[6] = { 0 };
	int ticketsSold = 0;
	Location* location = nullptr;

public:

	Event() {
		name = nullptr;
		strcpy_s(date, 11, "00/00/0000"); // dd/mm/yyyy
		strcpy_s(time, 6, "00:00"); // hh:mm
		ticketsSold = 0;
		location = nullptr;
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
	}

	~Event() {
		delete[] name;
		//finishCurrentEvent(*this->location, ticketsSold);
	}

	friend ostream& operator<<(ostream& console, Event& event);
	friend istream& operator>>(istream& console, Event& event);

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

class Ticket {
protected:
	int id = -1;
	Event* event = nullptr;
	ticketType zone = OTHER;
	float price = 0;

	//static int ticketsSold;


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
	Ticket() {
		id = generateTicketId();
		event = nullptr;
		zone = OTHER;
		price = 0;
		//addElementToArray(ticketList, *this, ticketsSold); //tickets sold also increased here
	}

	Ticket(Event& event, ticketType zone, float price) {
		this->id = generateTicketId();
		this->event = &event;
		this->zone = zone;
		if (price < 0)
			throw exception("negative value not allowed for price");
		this->price = price;
		//addElementT(oArray(ticketList, *this, ticketsSold);
		if (this->event != nullptr)
			this->event++;
	}

};
