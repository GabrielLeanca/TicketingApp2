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

	//end of tests
	//
	//
}