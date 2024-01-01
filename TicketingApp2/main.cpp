#include <stdio.h>
#include "Classes.h"
using namespace std;

//tests
void deconstructorTest() {
	Location deconstructThis("adressd", "named", 43);
	cout << endl << vectLoc[3]->getAddress();
}
//end of tests
//
//


int main() {


	//tests
	ticketType type = CATEGORY1;
	cout << type;

	Location location;

	Location locationNotDefault("city1, street1", "place1", 50);

	cout << endl << "not default: " << locationNotDefault.getName();
	cout << endl << "second in vector: " << vectLoc[1]->getName();

	location = locationNotDefault;
	Location copyL(locationNotDefault);

	cout << endl << "assignment works: " << vectLoc[0]->getName() << " also address: " << vectLoc[2]->getAddress();

	deconstructorTest();
	//cout << endl << vectLoc[3]->getAddress();
	/*
	location.setName("brandName");
	cout << endl << "name getter and setter: " << location.getName();

	location.setCapacity(100);
	cout << endl << "capacity getter and setter: " << location.getCapacity();

	int* previousEventsArray = new int[3];
	for (int i = 0; i < 3; i++) {
		previousEventsArray[i] = i + 1;
	}
	location.setTicketsSoldPreviously(previousEventsArray, 3);
	cout << endl;
	previousEventsArray = location.getTicketsSoldPreviously();
	for (int i = 0; i < 3; i++) {
		cout << previousEventsArray[i] << " ";
	}
	cout << endl << "number of events (should be 3): " << location.getNoPreviousEvents();

	cout << endl << location.getRating() << " " << location.getRatingWeight();
	location.setRating(3, 2);
	cout << endl << location.getRating() << " " << location.getRatingWeight();

	cout << endl << "tickets on first event: " << location[0];
	location[0] = 7;
	cout << endl << "tickets on first event: " << location[0];

	locationNotDefault = location;
	cout << locationNotDefault;
	//cin >> locationNotDefault;
	//cout << locationNotDefault;
	*/

	Event event;

	Event eventNotDefault("name1", "01/01/2000", "20:00", location);
	//cout << event;
	Event copyEvent(eventNotDefault);
	//cout << copyEvent;
	event = copyEvent;
	//cout << event;
	event.setName("xyz");
	event.setDate("30/04/2002");
	event.setTime("10:10");
	event.setTicketsSold(10);
	event.setLocation(locationNotDefault);
	/*cout << endl << event.getName() << endl << event.getDate() << endl << event.getTime() << endl << event.getTicketsSold() << endl << event.getLocation()->getAddress();
	cin >> event;
	cout << event;*/
	Ticket ticket;
	//end of tests
	//
	//
}