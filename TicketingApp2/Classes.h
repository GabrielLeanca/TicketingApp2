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
};