#include "Classes.h"
using namespace std;

//tests
void deconstructorTest() {
	Location deconstructThis("adressd", "named", 43);
	cout << endl << Location::getVectLoc()[3]->getAddress();
}
//end of tests
//
//


int main() {
	srand(time(0));

	//tests
	ticketType type = CATEGORY1;
	cout << type;

	Location location;

	Location locationNotDefault("city1, street1", "place1", 50);

	cout << endl << "not default: " << locationNotDefault.getName();
	cout << endl << "second in vector: " << Location::getVectLoc()[1]->getName();

	location = locationNotDefault;
	Location copyL(locationNotDefault);

	cout << endl << "assignment works: " << Location::getVectLoc()[0]->getName() << " also address: " << Location::getVectLoc()[2]->getAddress();

	deconstructorTest();
	//cout << endl << Location::getVectLoc()[3]->getAddress();
	
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
	event.setTicketsSold(0);
	event.setLocation(locationNotDefault);
	/*cout << endl << event.getName() << endl << event.getDate() << endl << event.getTime() << endl << event.getTicketsSold() << endl << event.getLocation()->getAddress();
	cin >> event;
	cout << event;*/
	cout << endl << endl << endl;
	Ticket ticket;
	cout << endl << "tickets sold by event: " << event.getTicketsSold();
	Ticket ticketNotDefault(event, VIP, 10);
	cout << endl << "tickets sold by event: " << event.getTicketsSold();
	ticket = ticketNotDefault;
	Ticket ticketCopy(ticketNotDefault);
	cout << ticket << endl;
	//cin >> ticket;
	cout << endl << ticket;
	cout << endl << " " << ticket - 1 << " " << ticket + 1 << " " << ticket / 2 << " " << ticket * 2;
	ticket.setPrice(7);
	cout << endl << ticket.getPrice() << " " << ticket.getId();
	ticket.setEvent(&eventNotDefault);
	cout << endl << eventNotDefault.getName();
	cout << endl << ticket.getEvent()->getName();
	ticket.setZone(VIP);
	cout << endl << ticket.getZone();
	cout << endl << Ticket::getNoTk();

	cout << endl << Ticket::getVectTk()[0]->getZone();
	cout << endl << Ticket::getTicket(0).getZone();
	cout << Ticket::getTicket(0);

	cout << endl << event.getTicketsSold() << " " << eventNotDefault.getTicketsSold();
	cout << endl << (event<eventNotDefault) << (event <= eventNotDefault) << (event == eventNotDefault) << (event >= eventNotDefault) << (event>eventNotDefault);
	cout << endl << event.calculateFutureRevenue();
	cout << endl;
	for (int i = 0; i < Ticket::getNoTk(); i++) {
		cout << Ticket::getTicket(i).getEvent()->getName() << " " << Ticket::getTicket(i).getPrice() << endl;
	}
	cout << event.getName() << " " << eventNotDefault.getName() << " " << copyEvent.getName();
	event.setTicketPriceForEvent(50);
	cout << endl << event.calculateFutureRevenue();

	cout << endl << 1 + ticket << " " << 1 - ticket << " " << 2 * ticket << " " << 2 / ticket;


	cout << endl << endl;
	Location anotherLoc("anotherAdr", "another name", 40);
	cout << endl << anotherLoc.getNoPreviousEvents();
	Event anotherEvent("another name", "10/10/1010", "10:10", anotherLoc);
	cout << endl << anotherLoc.getNoPreviousEvents();
	Ticket anotherTk(anotherEvent, VIP, 50);
	Ticket anotherTk2(anotherEvent, VIP, 50);
	cout << endl << anotherLoc.getNoPreviousEvents();

	Location* pointerToEventLocation = anotherEvent.getLocation();
	
	cout << endl << endl << pointerToEventLocation->getNoPreviousEvents() << endl;
	
	for (int i = 0; i < pointerToEventLocation->getNoPreviousEvents(); i++)
		cout << pointerToEventLocation->getTicketsSoldPreviously()[i] << " ";
	anotherLoc.finishCurrentEvent(anotherEvent);
	cout << endl << endl << pointerToEventLocation->getNoPreviousEvents() << endl;
	for (int i = 0; i < pointerToEventLocation->getNoPreviousEvents(); i++)
		cout << pointerToEventLocation->getTicketsSoldPreviously()[i] << " ";
	anotherLoc.setMinimumPriceForLocation(70);
	cout << endl << anotherTk.getPrice();

	Location loc2;
	cout << endl << !loc2 << " " << !location;
	loc2 = 5;
	cout << endl << loc2.getRating() << " " << loc2.getRatingWeight();
	
	
	//end of tests
	//
	//
}